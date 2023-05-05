// Copyright Epic Games, Inc. All Rights Reserved.

#include "Endless_RunnerGameMode.h"
#include "Endless_RunnerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/EndlessRunnerGameInstance.h"
#include "Managers/TrackManager.h"
#include "Engine/EngineTypes.h"

#include "UObject/ConstructorHelpers.h"

AEndless_RunnerGameMode::AEndless_RunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//Store config settings here in case other classess need them
	LaneOffSets.Add(FVector(1550.f, 150.f, 200.f));
	LaneOffSets.Add(FVector(1550.f, 450.f, 200.f));
	LaneOffSets.Add(FVector(1550.f, 750.f, 200.f));

	TrackStartingPositions.Add(FVector(0.f, -1200.f, 0.f));
	TrackStartingPositions.Add(FVector(0.f,  1200.f, 0.f));
}

void AEndless_RunnerGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	GameInstance = Cast<UEndlessRunnerGameInstance>(GetWorld()->GetGameInstance());
}

void AEndless_RunnerGameMode::StartPlay()
{
	Super::StartPlay();
	LinkController();
	SpawnTracks();
	SpawnPlayers();
}

void AEndless_RunnerGameMode::LinkController() {
	DPController = CastChecked<ADualPlayerController>(GetWorld()->GetFirstPlayerController());
	DPController->UpdateTimeToBeat(GameInstance->GetCurrentHighScoreTime());
}
/// <summary>
/// Spawns tracks, registers them with game instance and then gets game instance to link them to each other for obstacle teleportation
/// </summary>
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
		TrackManager->ConfigureId(i);
		Instance->RegisterTracks(TrackManager);
	}
	Instance->LinkTracks();
}
/// <summary>
/// creates a player for each track manager and links them to the tracks as well as the Dual Player Controller
/// </summary>
void AEndless_RunnerGameMode::SpawnPlayers()
{
	UWorld* WorldRef = GetWorld();
	UEndlessRunnerGameInstance* Instance = Cast<UEndlessRunnerGameInstance>(GetWorld()->GetGameInstance());
	FVector SpawnPoint = StartingSpawnPoint;
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
	FActorSpawnParameters spawnParam;

	for (int i = 0; i < NumPlayers; i++) {
		TObjectPtr<ATrackManager> TrackManager = Instance->GetTrack(i);
		AEndless_RunnerCharacter* Character = WorldRef->SpawnActor<AEndless_RunnerCharacter>(CharacterImplementation, SpawnPoint + FVector(0.f, 0.f, 200.f), SpawnRotation, spawnParam);
		Character->SetPlayerId(i);
		Character->BindToTrack(TrackManager);
		Character->OnKilled.AddDynamic(this, &AEndless_RunnerGameMode::FinishGame);
		DPController->RegisterPlayer(Character, i);
	}

}


void AEndless_RunnerGameMode::FinishGame(int32 LosingPlayerId) {

	UGameplayStatics::SetGamePaused(GetWorld(),true);
	float realtimeSeconds = UGameplayStatics::GetTimeSeconds(GetWorld());
	FTimespan TimeToSubmit = FTimespan::FromSeconds(realtimeSeconds);
	GameInstance->CheckHighScore(TimeToSubmit);
	DPController->UpdateTimeToBeat(GameInstance->GetCurrentHighScoreTime());

}

void AEndless_RunnerGameMode::PauseGame() {
	const TObjectPtr<UWorld> WorldRef = GetWorld();
	if(UGameplayStatics::IsGamePaused(WorldRef)) {
		UGameplayStatics::SetGamePaused(WorldRef, false);
	}
	else {
		UGameplayStatics::SetGamePaused(WorldRef, true);
	}
}

/// <summary>
/// Overrides of base function for creating players
/// </summary>
/// <param name="NewPlayer"></param>
void AEndless_RunnerGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);


}