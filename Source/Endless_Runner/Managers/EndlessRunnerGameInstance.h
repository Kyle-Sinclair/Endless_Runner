// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TrackManager.h"

#include "../Endless_RunnerCharacter.h"
#include "Misc/Timespan.h"

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
	UPROPERTY(EditDefaultsOnly)
	FString ConfigurableSaveFilePathName;	
	FString SaveFilePathName;
	UPROPERTY(VisibleAnywhere)

	FTimespan CurrentHighScoreTime;
	virtual void Init() override;
	void AccessSaveFile();

public:
	UPROPERTY()
	int NumPlayers;
	void CheckHighScore(const FTimespan SubmittedScore);

public:
	void RegisterTracks(TObjectPtr<ATrackManager> TrackManager);
	FTimespan GetCurrentHighScoreTime();

	void SaveHighScoreToFile(FString FilePath, FString Data, bool& bAcccessSuccess, FString& OutMessage);
	FString LoadHighScoreFromFile(FString FilePath, bool& bAcccessSuccess, FString& OutMessage);

	TWeakObjectPtr<ATrackManager> GetTrack(int index);

};
