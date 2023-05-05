// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Managers/EndlessRunnerGameInstance.h"

#include "Endless_RunnerCharacter.h"
#include "Managers/TrackManager.h"
#include "Managers/DualPlayerController.h"

#include "Endless_RunnerGameMode.generated.h"


UCLASS(minimalapi)
class AEndless_RunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	/// <summary>
	/// AGameMode base functions
	/// </summary>
	AEndless_RunnerGameMode();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	virtual void StartPlay() override;

public:
	/// <summary>
	/// Configurable settings for game start up
	/// </summary>
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

	/// <summary>
	/// Public functions for player to control game state
	/// </summary>
	UFUNCTION()
	void FinishGame(int32 LosingPlayerId);
	void PauseGame();
	void QuitGame();

protected:
	
	/// <summary>
	/// Start Up Functions
	/// </summary>
	void LinkController();
	void SpawnTracks();
	void SpawnPlayers();

	/// <summary>
	/// In Game References
	/// </summary>
	TObjectPtr<ADualPlayerController> DPController;
	TObjectPtr<UEndlessRunnerGameInstance> GameInstance;

	/// <summary>
	/// In Game config settings
	/// </summary>
	TArray<FVector> LaneOffSets;
	TArray<FVector> TrackStartingPositions;

	
	
};



