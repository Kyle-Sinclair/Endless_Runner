// Copyright Epic Games, Inc. All Rights Reserved.

#include "Endless_RunnerGameMode.h"
#include "Endless_RunnerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/EndlessRunnerGameInstance.h"

#include "UObject/ConstructorHelpers.h"

AEndless_RunnerGameMode::AEndless_RunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	ObstacleRelativeOffsets.Add(FVector(250.f, -150.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(550.f, -150.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(850.f, -150.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(250.f, -450.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(550.f, -450.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(850.f, -450.f, -150.f)); 
	ObstacleRelativeOffsets.Add(FVector(250.f, -750.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(550.f, -750.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(850.f, -750.f, -150.f));

	LaneOffSets.Add(FVector(1550.f, 150.f, 200.f));
	LaneOffSets.Add(FVector(1550.f, 450.f, 200.f));
	LaneOffSets.Add(FVector(1550.f, 750.f, 200.f));

	TrackStartingPositions.Add(FVector(0.f, -1200.f, 0.f));
	TrackStartingPositions.Add(FVector(0.f,  1200.f, 0.f));
}

void AEndless_RunnerGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	//NumPlayers = 2;
	Super::InitGame(MapName, Options, ErrorMessage);
	
	
}

void AEndless_RunnerGameMode::StartPlay()
{
	Super::StartPlay();
	UWorld* WorldRef = GetWorld();

	UEndlessRunnerGameInstance* Instance = Cast<UEndlessRunnerGameInstance>(GetWorld()->GetGameInstance());

	FVector SpawnPoint = StartingSpawnPoint;
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
	FActorSpawnParameters spawnParam;
	for (int i = 0; i < NumPlayers; i++) {
		SpawnPoint = SpawnPoint + (i * SpawnOffset);
		//TObjectPtr<ATrackManager> TrackManager = GetWorld()->SpawnActor(TrackImplementation, &SpawnPoint, &SpawnRotation, spawnParam);
		TObjectPtr<ATrackManager> TrackManager = GetWorld()->SpawnActor<ATrackManager>(TrackImplementation, SpawnPoint, SpawnRotation, spawnParam);
		Instance->RegisterTracks(TrackManager);

	}
	FVector SpawnPosition = FVector(0.f, -800.f, 0.f);
	for (int i = 0; i < 2; i++) {
		AActor* playerSpawned = UGameplayStatics::CreatePlayer(WorldRef, i, true);
		if (playerSpawned) {
			SpawnPosition += FVector(0.f, i * 1200.f, 0.f);
			playerSpawned->SetActorLocation(SpawnPosition);
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("Actor reference worked"));

		}
		else {
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Blue, TEXT("Actor reference invalid"));
		}


	}
}

void AEndless_RunnerGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Red, TEXT("Actor reference valid"));

}

