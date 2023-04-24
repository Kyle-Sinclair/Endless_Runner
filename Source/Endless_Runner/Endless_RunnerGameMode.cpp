// Copyright Epic Games, Inc. All Rights Reserved.

#include "Endless_RunnerGameMode.h"
#include "Endless_RunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEndless_RunnerGameMode::AEndless_RunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	ObstacleRelativeOffsets.Add(FVector(250.f, -150.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(550.f, -150.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(850.f, -150.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(250.f, -450.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(550.f, -450.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(850.f, -450.f, -150.f)); 
	ObstacleRelativeOffsets.Add(FVector(250.f, -750.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(550.f, -750.f, -150.f));
	ObstacleRelativeOffsets.Add(FVector(850.f, -750.f, -150.f));

	LaneOffSets.Add(FVector(1550.f, 150.f, 200.f));
	LaneOffSets.Add(FVector(1550.f, 450.f, 200.f));
	LaneOffSets.Add(FVector(1550.f, 750.f, 200.f));

}
