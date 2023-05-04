// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameInstance.h"
#include "../Endless_RunnerGameMode.h"
#include "HAL/PlatformFilemanager.h"

void UEndlessRunnerGameInstance::Init() {
	Super::Init();
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

void UEndlessRunnerGameInstance::SaveHighScoreToFile(FString FilePath, bool& bAcccessSuccess, FString& OutMessage) {



}
FString UEndlessRunnerGameInstance::LoadHighScoreFromFile(FString FilePath, FString Data, bool& bAcccessSuccess, FString& OutMessage) {
	
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
