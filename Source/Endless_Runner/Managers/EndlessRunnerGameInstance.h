// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TrackManager.h"
#include "../Obstacle.h"

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
	///// Saving and Loading Functions ///////
	void SaveHighScoreToFile(FString FilePath, FString Data, bool& bAcccessSuccess, FString& OutMessage);
	FString LoadHighScoreFromFile(FString FilePath, bool& bAcccessSuccess, FString& OutMessage);
	void AccessSaveFile();


	///// Saving and Loading Fields ///////
	UPROPERTY(EditDefaultsOnly)
		FString ConfigurableSaveFilePathName;
	FString SaveFilePathName;


	///// Game Configuration ///////

	UPROPERTY(EditDefaultsOnly)
		FVector StartingSpawnPoint;
	UPROPERTY(EditDefaultsOnly)
		FVector SpawnOffset;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf< ATrackManager> TrackImplementation;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AEndless_RunnerCharacter> CharacterImplementation;


	///// In Game References ///////

public:
	UPROPERTY()
	int NumPlayers;
	void CheckHighScore(const FTimespan SubmittedScore);
	void RegisterTracks(TObjectPtr<ATrackManager> TrackManager);
	void LinkTracks();
	FTimespan GetCurrentHighScoreTime();

	TArray<TObjectPtr<ATrackManager>> PlayerTracks;
	
	UPROPERTY(VisibleAnywhere)

	FTimespan CurrentHighScoreTime;
	virtual void Init() override;

	TObjectPtr<ATrackManager> GetTrack(int index);



	

};
