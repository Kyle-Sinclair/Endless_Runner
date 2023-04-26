// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameInstance.h"



void UEndlessRunnerGameInstance::Init() {
	Super::Init();

	//Create A number of tracks equal to the number of players

	SpawnTracks();

	//Create player characters on each track and give them appropriate offsets

	SpawnPlayers();

	//Give each track an obstacle spawner and register delegate methods

	CreateObstacleSpawners();

	//Split the screen into an appropriate number of slices
	SplitScreen();

	PlayerTracks.Reserve(NumPlayers);

}

void UEndlessRunnerGameInstance::SpawnTracks()
{
	FVector SpawnPoint = StartingSpawnPoint;
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);

	for (int i = 0; i < NumPlayers; i++) {
		GetWorld()->SpawnActor<ATrackManager>(SpawnPoint + (i * SpawnOffset), SpawnRotation);
	}




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
