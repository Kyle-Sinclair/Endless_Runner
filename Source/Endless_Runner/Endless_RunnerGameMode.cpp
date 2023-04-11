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
}
