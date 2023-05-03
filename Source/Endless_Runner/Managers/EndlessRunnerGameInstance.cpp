// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameInstance.h"
#include "../Endless_RunnerGameMode.h"


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
