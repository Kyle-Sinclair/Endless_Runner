// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameInstance.h"
#include "../Endless_RunnerGameMode.h"


void UEndlessRunnerGameInstance::Init() {
	Super::Init();

	ConfigureGameInstance();

	//Create A number of tracks equal to the number of players


	//Create player characters on each track and give them appropriate offsets
	
	SpawnPlayers();

	//Give each track an obstacle spawner and register delegate methods

	CreateObstacleSpawners();

	//Split the screen into an appropriate number of slices
	SplitScreen();

	PlayerTracks.Reserve(NumPlayers);

}



void UEndlessRunnerGameInstance::SpawnPlayers()
{
	
}

void UEndlessRunnerGameInstance::CreateObstacleSpawners()
{

}

void UEndlessRunnerGameInstance::SplitScreen()
{

}

void UEndlessRunnerGameInstance::ConfigureGameInstance()
{
	
}void UEndlessRunnerGameInstance::RegisterTracks(TObjectPtr<ATrackManager> TrackManager)
{
	 PlayerTracks.Add(TrackManager);
	 if (PlayerTracks.Contains(TrackManager))
	 {
		 GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("Track Registered"));
	 }

}
