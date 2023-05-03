// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TrackManager.h"

#include "../Endless_RunnerCharacter.h"
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
		FVector StartingSpawnPoint;
	UPROPERTY(EditDefaultsOnly)
		FVector SpawnOffset;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf< ATrackManager> TrackImplementation;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AEndless_RunnerCharacter> CharacterImplementation;

	TArray<TObjectPtr<ATrackManager>> PlayerTracks;
	
	virtual void Init() override;
public:
	UPROPERTY()
	int NumPlayers;

public:
	void RegisterTracks(TObjectPtr<ATrackManager> TrackManager);
	TWeakObjectPtr<ATrackManager> GetTrack(int index);

};
