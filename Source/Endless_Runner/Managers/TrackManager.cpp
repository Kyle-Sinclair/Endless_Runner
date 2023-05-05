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
	ObstaclesToPort = 0;
	InitializeTrack();
	LinkTrackPieces();
}

// Called every frame
void ATrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RecieveObstacles();
	PortObstacles();
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
///// 
//Empty collection of teleported obstacles and move them to managed obstacle collection
void ATrackManager::RecieveObstacles() {
	const bool bAllowShrinking = false;
	TObjectPtr<AObstacle> ObstacleToBeRecieved;

	for (int32 Index = RecievedObstacles.Num() - 1; Index >= 0; --Index)
	{
		ObstacleToBeRecieved = RecievedObstacles[Index];
		if (ObstacleToBeRecieved->IsValidLowLevel())
		{
			CurrentObstacles.Emplace(ObstacleToBeRecieved);
			RecievedObstacles.RemoveAt(Index, 1, bAllowShrinking);
		}

	}
}
/// <summary>
/// Checks to see if should port an obstacle to the other track based on
/// the value of ObstaclesToPort
/// Has to be called before Shift obstacles to avoid access competition
/// </summary>
void ATrackManager::PortObstacles() {

	while (ObstaclesToPort > 0) {

		ObstaclesToPort--;
		const float ChanceToPort = FMath::RandRange(0, 100);
		const bool bAllowShrinking = false;
		TObjectPtr<AObstacle> ObstacleToBeRemoved;

		if (ChanceToPort < PortProbability) {

			int32 randomIndex = FMath::RandHelper(CurrentObstacles.Num());

			if (randomIndex == 0)
			{
				return;
			}
			ObstacleToBeRemoved = CurrentObstacles[randomIndex];
			if (ObstacleToBeRemoved)
			{
				CurrentObstacles.RemoveAt(randomIndex, 1, bAllowShrinking);
				LinkedTrack->RecieveTeleportedObstacle(ObstacleToBeRemoved);
			}
		}
		//Chance to port climbs until hit
		PortProbability++;
		PortProbability = FMath::Clamp(PortProbability, 10.f, 50.f);
	}
}
/// <summary>
/// Shfit all track pieces by the same amount
/// </summary>
/// <param name="DeltaTime"></param>
void ATrackManager::ShiftTrack(float const DeltaTime) {
	
	float posDelta = DeltaTime  * -TrackSpeed;
	for (auto& TrackPiece : CurrentTrackPieces)
	{
		TrackPiece->AddActorWorldOffset(FVector(posDelta, 0.f, 0.f));
	}
	TrackDelta += -posDelta;
}

/// <summary>
/// Shift all obstacles managed by this track the same amount as the relevant track pieces
/// </summary>
/// <param name="DeltaTime"></param>
void ATrackManager::ShiftObstacles(float const DeltaTime) {

	float posDelta = DeltaTime * -TrackSpeed;
	for (auto& Obstacle : CurrentObstacles)
	{
		if (Obstacle->IsValidLowLevel()) {
			Obstacle->AddActorWorldOffset(FVector(posDelta, 0.f, 0.f));
		}
	}
}

/// <summary>
/// Clear any obstacles that have moved past a certain threshold and 
/// add values to chance to port for each removed obstacle
/// </summary>
void ATrackManager::ClearObstacles() {
	const bool bAllowShrinking = false;
	TWeakObjectPtr<AObstacle> ObstacleToBeRemoved;

	//Step through the array backwards to avoid array number becoming lower
	//than index
	for (int32 Index = CurrentObstacles.Num() - 1; Index >= 0; --Index)
	{
		ObstacleToBeRemoved = CurrentObstacles[Index];
		if (ObstacleToBeRemoved->IsValidLowLevel())
		{
			if (CurrentObstacles[Index]->GetActorLocation().X < 700.f) 
			{
				CurrentObstacles.RemoveAt(Index, 1, bAllowShrinking);
				ObstaclesToPort++;
				ObstacleToBeRemoved->Destroy();
			}
		}
	}
}
/// <summary>
/// Difficulty tracks up over time
/// </summary>
/// <param name="DeltaTime"></param>
void ATrackManager::UpdateDifficulty(float const DeltaTime) {
	TrackDifficulty += DeltaTime * 0.1;
}


void ATrackManager::SwapHeadWithTail()
{

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
	TArray<FVector> ObstacleRelativeOffsets = HeadTrackPiece->ObstacleRelativeOffsets;

	for (FVector vec : ObstacleRelativeOffsets)
	{
		ChanceToSpawn = FMath::RandRange(0, 100);
		if (ChanceToSpawn < TrackDifficulty) {
			AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(PossibleObstacles[0], HeadTrackPiece->TrackSeamPoint->GetComponentLocation() - vec, GetActorRotation());
			CurrentObstacles.Emplace(Obstacle);
		}
	}
}



void ATrackManager::RecieveTeleportedObstacle(TObjectPtr<AObstacle> Obstacle) {
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("Recieving Obstacle"));
	//int32 DepositLength = FMath::RandRange(0, 100);
	if (Obstacle) {
		RecievedObstacles.Emplace(Obstacle);
		FVector LocalOffset = GetLocalOffset();
		bool bSweep = false;
		FHitResult result;
		Obstacle->AddActorLocalOffset(LocalOffset,bSweep,&result);
		if (result.bBlockingHit) {
			Obstacle->AddActorLocalOffset(FVector(0.f, 0.f, 150.f));
		}
	}
}
///// Start up Methods //////

/// <summary>
/// Create all the track pieces managed by this track manager
/// </summary>
void ATrackManager::InitializeTrack()
{
	CurrentTrackPieces.Reserve(TrackLength);

	TObjectPtr<ATrackPiece> CreatedTrackPiece;

	//Spawn first track segment and make it both tail and head segment
	CreatedTrackPiece = GetWorld()->SpawnActor<ATrackPiece>(PossibleTrackPieces[0], GetActorLocation(), GetActorRotation());
	CreatedTrackPiece->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	CurrentTrackPieces.Add(CreatedTrackPiece);
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
/// <summary>
//Link Track Pieces to each other so that the head and tail track piece
//can be easily updated
/// </summary>

void ATrackManager::LinkTrackPieces()
{
	CurrentTrackPieces[0]->NextTrackPiece = CurrentTrackPieces[1];
	CurrentTrackPieces[0]->PreviousTrackPiece = CurrentTrackPieces[TrackLength - 1];
	for (int i = 1; i < CurrentTrackPieces.Num(); i++) {

		CurrentTrackPieces[i]->PreviousTrackPiece = CurrentTrackPieces[(i - 1) % TrackLength];
		CurrentTrackPieces[i]->NextTrackPiece = CurrentTrackPieces[(i + 1) % TrackLength];
	}


}
///// Utility Methods //////

/// <summary>
/// The offset to move an obstacle to the corresponding track's same position
/// Not the best solution but couldn't get a mapping to work better
/// </summary>
/// <returns></returns>
FVector ATrackManager::GetLocalOffset() {
	if (TrackId == 0) {
		return FVector(0.f, -950.f, 0.f);
	}
	else
		return FVector(0.f, 950.f, 0.f);
}
/// <summary>
/// Configures track id. Track ID maps to this track managers index in Game Instance's 
/// Player Track Array
/// </summary>
/// <param name="newTrackId"></param>
void ATrackManager::ConfigureId(const int32 newTrackId) {
	TrackId = newTrackId;
}

/// <summary>
/// Probabiltiy to port is reset whenever this Track Manager's character takes damage
/// </summary>
void ATrackManager::ResetProbability() {
	PortProbability = 10.f;
}

