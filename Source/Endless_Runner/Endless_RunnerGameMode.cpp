// Copyright Epic Games, Inc. All Rights Reserved.

#include "Endless_RunnerGameMode.h"
#include "Endless_RunnerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/EndlessRunnerGameInstance.h"

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

	TrackStartingPositions.Add(FVector(0.f, -1200.f, 0.f));
	TrackStartingPositions.Add(FVector(0.f,  1200.f, 0.f));
}

void AEndless_RunnerGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	//NumPlayers = 2;
	Super::InitGame(MapName, Options, ErrorMessage);
	
	
}

void AEndless_RunnerGameMode::StartPlay()
{
	Super::StartPlay();
	SpawnTracks();
	SpawnPlayers();
	
}

void AEndless_RunnerGameMode::SpawnTracks()
{
	UWorld* WorldRef = GetWorld();
	UEndlessRunnerGameInstance* Instance = Cast<UEndlessRunnerGameInstance>(GetWorld()->GetGameInstance());
	FVector SpawnPoint = StartingSpawnPoint;
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
	FActorSpawnParameters spawnParam;


	for (int i = 0; i < NumPlayers; i++) {
		SpawnPoint = SpawnPoint + (i * SpawnOffset);
		TObjectPtr<ATrackManager> TrackManager = WorldRef->SpawnActor<ATrackManager>(TrackImplementation, SpawnPoint, SpawnRotation, spawnParam);
		Instance->RegisterTracks(TrackManager);

	}
}

void AEndless_RunnerGameMode::SpawnPlayers()
{
	FVector SpawnPosition = FVector(0.f, -800.f, 200.f);
	FActorSpawnParameters SpawnParam;
	UWorld* WorldRef = GetWorld();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	for (int i = 0; i < 2; i++) {

		APawn* playerSpawned =Cast<APawn>( WorldRef->SpawnActor<AActor>(CharacterImplementation, SpawnPosition, FRotator(0.f, 0.f, 0.f), SpawnParam));
		//APlayerController* playerSpawned = UGameplayStatics::CreatePlayer(WorldRef, -1, true);
		if (playerSpawned == nullptr) {
			UE_LOG(LogTemp, Warning,TEXT( "Nullpointer found"));
			return;
		}
		//playerSpawned->GetPawn()->SetActorLocation(SpawnPosition);
		playerSpawned->SetActorLocation(SpawnPosition);
		playerSpawned->PossessedBy(PlayerController);
		SpawnPosition += FVector(0.f, (i + 1) * 2400.f, 0.f);
	}
}

void AEndless_RunnerGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	//Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Red, TEXT("Actor reference valid"));

}

