// Fill out your copyright notice in the Description page of Project Settings.
#include "TrackManager.h"
#include "../Endless_RunnerGameMode.h"
#include "Math/UnrealMathUtility.h"
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
	//LinkTrackPieces();
	

	

}

// Called every frame
void ATrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShiftTrack(DeltaTime);
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



void ATrackManager::InitializeTrack()
{

	
	CurrentTrackPieces.Emplace(GetWorld()->SpawnActor<ATrackPiece>(PossibleTrackPieces[0], GetActorLocation(), GetActorRotation()));

	
	CurrentTrackPieces.Reserve(TrackLength);
	//Spawn first track segment and make it both tail and head segment
	CurrentTrackPieces.Emplace(GetWorld()->SpawnActor<ATrackPiece>(PossibleTrackPieces[0], GetActorLocation(), GetActorRotation()));
	TailTrackPiece = CurrentTrackPieces[0];
	HeadTrackPiece = TailTrackPiece;
	//Spawn each subsequent track piece and move the head to each one

	for (int i = 1; i < TrackLength; i++) {
		const FVector SpawnLocation = HeadTrackPiece->TrackSeamPoint->GetComponentLocation();
		FRotator  SpawnRotation = HeadTrackPiece->TrackSeamPoint->GetComponentRotation();
		CurrentTrackPieces.Emplace(GetWorld()->SpawnActor<ATrackPiece>(PossibleTrackPieces[0], SpawnLocation, SpawnRotation));
		HeadTrackPiece = CurrentTrackPieces[i];
		FObstacleCollection collection;
	}

	HeadTrackPiece = CurrentTrackPieces[TrackLength - 1];
	
}
void ATrackManager::LinkTrackPieces()
{
	CurrentTrackPieces[0]->NextTrackPiece = CurrentTrackPieces[1];
	CurrentTrackPieces[0]->PreviousTrackPiece = CurrentTrackPieces[TrackLength - 1];
	for (int i = 1; i < CurrentTrackPieces.Num(); i++) {
		//UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *CurrentTrackPieces[i]->GetName());
		CurrentTrackPieces[i]->PreviousTrackPiece = CurrentTrackPieces[(i - 1) % 10];
		CurrentTrackPieces[i]->NextTrackPiece = CurrentTrackPieces[(i + 1) % 10];
	}


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

	
}

void ATrackManager::SpawnObstaclesOnTrack()
{
	float ChanceToSpawn;
	
	AEndless_RunnerGameMode* mymode = Cast<AEndless_RunnerGameMode>(GetWorld()->GetAuthGameMode());
	TArray<FVector> ObstacleRelativeOffsets = mymode->ObstacleRelativeOffsets;

	for (FVector vec : ObstacleRelativeOffsets)
	{
		ChanceToSpawn = FMath::RandRange(0, 100);
		if (ChanceToSpawn < TrackDifficulty) {
			AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(PossibleObstacles[0], HeadTrackPiece->TrackSeamPoint->GetComponentLocation() - vec, GetActorRotation());
			HeadTrackPiece->AttachObstacleToTrackPiece(vec, Obstacle);
		}
	}
}

void ATrackManager::RemoveTrackObstacles(TWeakObjectPtr<ATrackPiece> TrackSegmentToBeCleared)
{
	TArray<AActor*> Obstacles;
	TrackSegmentToBeCleared->GetAttachedActors(Obstacles);
	for (AActor* Obstacle : Obstacles)
	{
		Obstacle->Destroy();
	}
}
