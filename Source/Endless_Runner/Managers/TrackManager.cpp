// Fill out your copyright notice in the Description page of Project Settings.
#include "TrackManager.h"

#include "../TrackPiece.h"


// Sets default values
ATrackManager::ATrackManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ExitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Exit Collider"));

}

// Called when the game starts or when spawned
void ATrackManager::BeginPlay()
{
	Super::BeginPlay();
	TrackCount = 0;
	TrackDelta = 0;
	CurrentTrackPieces.Emplace(GetWorld()->SpawnActor<ATrackPiece>(PossibleTrackPieces[0], FVector(0.f, 0.f, 0.f), GetActorRotation()));
	TailTrackPiece = CurrentTrackPieces[0];
	HeadTrackPiece = TailTrackPiece;
	
	InitializeTrack();
	LinkTrackPieces();
	HeadTrackPiece = CurrentTrackPieces[9];
	TailTrackPiece = CurrentTrackPieces[0];

}

// Called every frame
void ATrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShiftTrack(DeltaTime);
	if (TrackDelta > 1500.f) {
		TrackDelta -= 1500.f;
	}
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-2, 15.0f, FColor::Blue, FString::Printf(TEXT("Position delta is % f"), TrackDelta));
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
	for (int i = 1; i < 10; i++) {
		const FVector SpawnLocation = HeadTrackPiece->TrackSeamPoint->GetComponentLocation();
		FRotator  SpawnRotation = HeadTrackPiece->TrackSeamPoint->GetComponentRotation();
		CurrentTrackPieces.Emplace(GetWorld()->SpawnActor<ATrackPiece>(PossibleTrackPieces[0], SpawnLocation, SpawnRotation));
		HeadTrackPiece = CurrentTrackPieces[i];

	}

}
void ATrackManager::LinkTrackPieces()
{
	CurrentTrackPieces[0]->NextTrackPiece = CurrentTrackPieces[1];
	CurrentTrackPieces[0]->PreviousTrackPiece = CurrentTrackPieces[9];
	for (int i = 1; i < CurrentTrackPieces.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *CurrentTrackPieces[i]->GetName());
		CurrentTrackPieces[i]->PreviousTrackPiece = CurrentTrackPieces[(i - 1) % 10];
		CurrentTrackPieces[i]->NextTrackPiece = CurrentTrackPieces[(i + 1) % 10];
	}


}