// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Endless_RunnerCharacter.h"
#include "Managers/TrackManager.h"
#include "Managers/DualPlayerController.h"

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
		int32 StartingHealth;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf< ATrackManager> TrackImplementation;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AEndless_RunnerCharacter> CharacterImplementation;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ADualPlayerController> DualPlayerControllerImplmentation;
	TArray<FVector> ObstacleRelativeOffsets;
	UFUNCTION()
	void FinishGame(int32 LosingPlayerId);
protected:
	void LinkController();

	void SpawnTracks();
	void SpawnPlayers();
	TObjectPtr<ADualPlayerController> DPController;

	TArray<FVector> LaneOffSets;
	TArray<FVector> TrackStartingPositions;

	
	
};



