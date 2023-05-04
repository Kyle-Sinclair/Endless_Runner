// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameInstance.h"
#include "../Endless_RunnerGameMode.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Paths.h"

#include "Misc/Timespan.h"

void UEndlessRunnerGameInstance::Init() {
	Super::Init();
	SaveFilePathName = FPaths::ConvertRelativePathToFull(ConfigurableSaveFilePathName);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, SaveFilePathName);

	AccessSaveFile();
}
TWeakObjectPtr<ATrackManager> UEndlessRunnerGameInstance::GetTrack(int index) {

	return PlayerTracks[index];
}

void UEndlessRunnerGameInstance::RegisterTracks(TObjectPtr<ATrackManager> TrackManager)
{
	 PlayerTracks.Add(TrackManager);
	 if (PlayerTracks.Contains(TrackManager))
	 {
		 GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("Track Registered"));
	 }

}


void UEndlessRunnerGameInstance::AccessSaveFile() {
	if (!SaveFilePathName.IsEmpty()) {
		bool SuccessfulSave;
		FString out;
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveFilePathName)) {
			
			FTimespan InitialTimeSpan = FTimespan::Zero();
			FString EmptyData = InitialTimeSpan.ToString();
			SaveHighScoreToFile(SaveFilePathName, EmptyData, SuccessfulSave, out);
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("No save game, making new save"));

		}
		FString currentHighScore = LoadHighScoreFromFile(SaveFilePathName, SuccessfulSave, out);
		FTimespan highestTimespan;
		FTimespan::Parse(currentHighScore,highestTimespan);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, currentHighScore);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, highestTimespan.ToString());
		if (highestTimespan.IsZero()) {
			highestTimespan = FTimespan::Zero();
		}
		CurrentHighScoreTime = highestTimespan;
		
	}
	//CurrentHighScoreTime = FTimespan::Zero();
}

void UEndlessRunnerGameInstance::SaveHighScoreToFile(FString FilePath, FString Data, bool& bAcccessSuccess, FString& OutMessage) {

	if (FFileHelper::SaveStringToFile(Data, *FilePath)) {
		bAcccessSuccess = true;
		OutMessage = FString::Printf(TEXT("File Saved Successfully"));
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, OutMessage);

	}
	else {
		bAcccessSuccess = false;
		OutMessage = FString::Printf(TEXT("Failed to save file"));
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, OutMessage);

	}

}
FString UEndlessRunnerGameInstance::LoadHighScoreFromFile(FString FilePath, bool& bAcccessSuccess, FString& OutMessage) {
	
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath)) {
		bAcccessSuccess = false;
		OutMessage = FString::Printf(TEXT("Couldn't access file at this file path - %s"), *FilePath);
	}
	FString RetValue = "";

	if (!FFileHelper::LoadFileToString(RetValue, *FilePath)) {
		bAcccessSuccess = false;
		OutMessage = FString::Printf(TEXT("Couldn't process file as a string at path - %s"), *FilePath);
	}

	bAcccessSuccess = true;
	return RetValue;
}

void UEndlessRunnerGameInstance::CheckHighScore(const FTimespan SubmittedTimespan) {
	if (SubmittedTimespan - CurrentHighScoreTime > 0) {

		FString Data = SubmittedTimespan.ToString();
		bool bSuccessfulSave;
		FString out;
		SaveHighScoreToFile(SaveFilePathName, Data, bSuccessfulSave, out);
		if (bSuccessfulSave) {
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("Saving new high score"));
		}
		CurrentHighScoreTime = SubmittedTimespan;

	}

}

FTimespan UEndlessRunnerGameInstance::GetCurrentHighScoreTime() {
	//return FTimespan::Zero();
	return CurrentHighScoreTime;
}
