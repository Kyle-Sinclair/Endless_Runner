// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TrackManager.h"
#include "EndlessRunnerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_RUNNER_API UEndlessRunnerGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
		int NumPlayers; 
	UPROPERTY(EditDefaultsOnly)
		FVector StartingSpawnPoint;
	UPROPERTY(EditDefaultsOnly)
		FVector SpawnOffset;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf< ATrackManager> TrackImplementation;

	TArray<TSubclassOf<ATrackManager>> PlayerTracks;

	virtual void Init() override;
	void SpawnTracks();
	void SpawnPlayers();
	void CreateObstacleSpawners();
	void SplitScreen();
};
