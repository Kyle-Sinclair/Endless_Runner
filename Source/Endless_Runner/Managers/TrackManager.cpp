// Fill out your copyright notice in the Description page of Project Settings.
#include "TrackManager.h"
#include "../Endless_RunnerGameMode.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

#include "../TrackPiece.h"


// Sets default values
ATrackManager::ATrackManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

ATrackManager::~ATrackManager()
{

}

// Called when the game starts or when spawned
void ATrackManager::BeginPlay()
{
	Super::BeginPlay();

	TrackDelta = 0.f;
	TrackDifficulty = 5.f;

	InitializeTrack();
	LinkTrackPieces();




	

}

// Called every frame
void ATrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShiftTrack(DeltaTime);
	ShiftObstacles(DeltaTime);
	ClearObstacles();
	UpdateDifficulty(DeltaTime);
	if (TrackDelta > 900.f) {
		TrackDelta -= 900.f;
		SwapHeadWithTail();
		SpawnObstaclesOnTrack();
	}

	
}

void ATrackManager::ShiftTrack(float const DeltaTime) {
	
	float posDelta = DeltaTime  * -TrackSpeed;
	for (auto& TrackPiece : CurrentTrackPieces)
	{
		TrackPiece->AddActorWorldOffset(FVector(posDelta, 0.f, 0.f));
	}
	TrackDelta += -posDelta;
}
void ATrackManager::ShiftObstacles(float const DeltaTime) {

	float posDelta = DeltaTime * -TrackSpeed;
	for (auto& Obstacle : CurrentObstacles)
	{
		if (Obstacle->IsValidLowLevel()) {
			Obstacle->AddActorWorldOffset(FVector(posDelta, 0.f, 0.f));
		}
	}
}
void ATrackManager::ClearObstacles() {
	const bool bAllowShrinking = false;
	TWeakObjectPtr<AObstacle> ObstacleToBeRemoved;

	for (int32 Index = CurrentObstacles.Num() - 1; Index >= 0; --Index)
	{
		ObstacleToBeRemoved = CurrentObstacles[Index];
		if (ObstacleToBeRemoved->IsValidLowLevel())
		{
			if (CurrentObstacles[Index]->GetActorLocation().X < 700.f) 
			{
				CurrentObstacles.RemoveAt(Index, 1, bAllowShrinking);
				PortObstacles();
				ObstacleToBeRemoved->Destroy();
			}
		}
		
	}
}
void ATrackManager::UpdateDifficulty(float const DeltaTime) {
	TrackDifficulty += DeltaTime * 0.1;
}


void ATrackManager::InitializeTrack()
{
	CurrentTrackPieces.Reserve(TrackLength);

	TObjectPtr<ATrackPiece> CreatedTrackPiece;

	//Spawn first track segment and make it both tail and head segment
	CreatedTrackPiece = GetWorld()->SpawnActor<ATrackPiece>(PossibleTrackPieces[0], GetActorLocation(), GetActorRotation());
	CreatedTrackPiece->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	CurrentTrackPieces.Add( CreatedTrackPiece);
	TailTrackPiece = CurrentTrackPieces[0];
	HeadTrackPiece = TailTrackPiece;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	//Spawn each subsequent track piece and move the head to each one
	UWorld* WorldRef = GetWorld();
	for (int i = 1; i < TrackLength; i++) {
		const FVector SpawnLocation = HeadTrackPiece->TrackSeamPoint->GetComponentLocation();
		FRotator  SpawnRotation = HeadTrackPiece->TrackSeamPoint->GetComponentRotation();
		
		CreatedTrackPiece = WorldRef->SpawnActor<ATrackPiece>(PossibleTrackPieces[0], SpawnLocation, SpawnRotation, SpawnParams);
		CreatedTrackPiece->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		CurrentTrackPieces.Emplace(CreatedTrackPiece);
		HeadTrackPiece = CurrentTrackPieces[i];
	}

	HeadTrackPiece = CurrentTrackPieces[TrackLength - 1];
}
void ATrackManager::LinkTrackPieces()
{
	CurrentTrackPieces[0]->NextTrackPiece = CurrentTrackPieces[1];
	CurrentTrackPieces[0]->PreviousTrackPiece = CurrentTrackPieces[TrackLength - 1];
	for (int i = 1; i < CurrentTrackPieces.Num(); i++) {

		CurrentTrackPieces[i]->PreviousTrackPiece = CurrentTrackPieces[(i - 1) % TrackLength];
		CurrentTrackPieces[i]->NextTrackPiece = CurrentTrackPieces[(i + 1) % TrackLength];
	}

	PlayerTrackPiece = TailTrackPiece->NextTrackPiece;

}

void ATrackManager::SwapHeadWithTail()
{
	RemoveTrackObstacles(TailTrackPiece);

	//Find the attachment position for current head track piece and move tail there
	const FVector SpawnLocation = HeadTrackPiece->TrackSeamPoint->GetComponentLocation();
	TailTrackPiece->SetActorLocation(SpawnLocation);

	//Swap head and tail pointers to new segments 
	TWeakObjectPtr<ATrackPiece> temp = TailTrackPiece->NextTrackPiece;
	HeadTrackPiece = TailTrackPiece;
	TailTrackPiece = temp;
	PlayerTrackPiece = PlayerTrackPiece->NextTrackPiece;
	
}

void ATrackManager::SpawnObstaclesOnTrack()
{
	float ChanceToSpawn;
	
	//AEndless_RunnerGameMode* mymode = Cast<AEndless_RunnerGameMode>(GetWorld()->GetAuthGameMode());
	//mymode->ObstacleRelativeOffsets;

	TArray<FVector> ObstacleRelativeOffsets = HeadTrackPiece->ObstacleRelativeOffsets;
	for (FVector vec : ObstacleRelativeOffsets)
	{
		ChanceToSpawn = FMath::RandRange(0, 100);
		if (ChanceToSpawn < TrackDifficulty) {
			AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(PossibleObstacles[0], HeadTrackPiece->TrackSeamPoint->GetComponentLocation() - vec, GetActorRotation());
			CurrentObstacles.Emplace(Obstacle);
			//HeadTrackPiece->AttachObstacleToTrackPiece(vec, Obstacle);
		}
	}
}

void ATrackManager::RemoveTrackObstacles(TWeakObjectPtr<ATrackPiece> TrackSegmentToBeCleared)
{
	//Don't like that this array is created every time. 
	//TODO: See if UE has non-destructive allocation for resuable arrays
	//TArray<AActor*> Obstacles;
	//TrackSegmentToBeCleared->GetAttachedActors(Obstacles);
	//float ChanceToPort = 0.f;
	//for (AActor* Obstacle : Obstacles)
	//{
	//	ChanceToPort = FMath::RandRange(0, 100);

	//	if (ChanceToPort < PortProbability) {
	//		//PlayerTrackPiece->NextTrackPiece->NextTrackPiece->PortObstacle(PortDepth);
	//		//PlayerTrackPiece->NextTrackPiece->NextTrackPiece->RemoveOneObstacle(PortDepth);
	//		//TArray<AActor*> Obstacles;
	//		//PlayerTrackPiece->NextTrackPiece->NextTrackPiece->GetAttachedActors( Obstacles);
	//		
	//	}
	//	PortProbability++;
	//	PortProbability = FMath::Clamp(PortProbability, 10.f, 100.f);
	//	Obstacle->Destroy();
	//	
	//}
}
void ATrackManager::PortObstacles() {

	const float ChanceToPort = FMath::RandRange(0, 100);
	const bool bAllowShrinking = false;
	TWeakObjectPtr<AObstacle> ObstacleToBeRemoved;
	if (ChanceToPort < PortProbability) {

		int32 randomIndex = FMath::RandHelper(CurrentObstacles.Num()); 

		if (randomIndex == 0) 
		{
			return;
		}
		ObstacleToBeRemoved = CurrentObstacles[randomIndex];
		if (ObstacleToBeRemoved->IsValidLowLevel())
		{
			CurrentObstacles.RemoveAt(randomIndex, 1, bAllowShrinking);
			ObstacleToBeRemoved->Destroy();
		}
	}
}


void ATrackManager::RecieveTeleportedObstacle(TObjectPtr<AActor> Obstacle) {
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("Recieving Obstacle"));
	int32 DepositLength = FMath::RandRange(0, 100);
}

void ATrackManager::ConfigureId(const int32 newTrackId) {
	TrackId = newTrackId;
}
void ATrackManager::ResetProbability() {
	PortProbability = 10.f;
}

