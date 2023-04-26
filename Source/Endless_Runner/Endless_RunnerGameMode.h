// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Endless_RunnerCharacter.h"
#include "Managers/TrackManager.h"

#include "Endless_RunnerGameMode.generated.h"

UCLASS(minimalapi)
class AEndless_RunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEndless_RunnerGameMode();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	virtual void StartPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
		int NumPlayers; 
	UPROPERTY(EditDefaultsOnly)
		FVector StartingSpawnPoint;
	UPROPERTY(EditDefaultsOnly)
		FVector SpawnOffset;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf< ATrackManager> TrackImplementation;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AEndless_RunnerCharacter> CharacterImplementation;


	TArray<FVector> ObstacleRelativeOffsets;
	TArray<FVector> LaneOffSets;
	TArray<FVector> TrackStartingPositions;

	
	
};



