// Fill out your copyright notice in the Description page of Project Settings.
#include "DualPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Endless_RunnerGameMode.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "Misc/Timespan.h"

ADualPlayerController::ADualPlayerController() {
	InputComponent = CreateDefaultSubobject<UInputComponent>("Input Component");
	HUD = CreateDefaultSubobject<UHUDWidget>("HUD");
}
///// Overridden functions //////

void ADualPlayerController::BeginPlay()
{

	GameMode = Cast<AEndless_RunnerGameMode>(GetWorld()->GetAuthGameMode());
	int32 id = GetLocalPlayer()->GetControllerId();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

	SetupPlayerInputComponent();
	HUD = CreateWidget<UHUDWidget>(this, HUDImplementation);
	HUD->AddToPlayerScreen(9999);
}


/// <summary>
/// This must be overridden in order for the controller to process input
/// commands
/// </summary>
/// <param name="DeltaSeconds"></param>
void ADualPlayerController::PlayerTick(float DeltaSeconds) {
	Super::PlayerTick(DeltaSeconds);
	float realtimeSeconds = UGameplayStatics::GetTimeSeconds(GetWorld());
	HUD->UpdateCurrentScore(FTimespan::FromSeconds(realtimeSeconds));
}

void ADualPlayerController::SetupPlayerInputComponent()
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->FindComponentByClass<UEnhancedInputComponent>());
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ADualPlayerController::JumpPlayer1);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADualPlayerController::MovePlayer1);
	EnhancedInputComponent->BindAction(JumpAction2, ETriggerEvent::Completed, this, &ADualPlayerController::JumpPlayer2);
	EnhancedInputComponent->BindAction(MoveAction2, ETriggerEvent::Triggered, this, &ADualPlayerController::MovePlayer2);
	EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ADualPlayerController::PauseGame);
}
/// <summary>
/// Binds game mode created characters to this controller
/// </summary>
/// <param name="NewCharacter"></param>
/// <param name="index"></param>
void ADualPlayerController::RegisterPlayer(TObjectPtr<AEndless_RunnerCharacter> NewCharacter, int index) {
	if (index == 0) {
		Player1 = NewCharacter;
		Player1->OnHealthUpdated.AddDynamic(this, &ADualPlayerController::UpdateHealthUI);
		Player1->Health = GameMode->StartingHealth;
		UpdateHealthUI(Player1->Health, 0);
		
	}
	else {
		Player2 = NewCharacter;
		Player2->OnHealthUpdated.AddDynamic(this, &ADualPlayerController::UpdateHealthUI);
		Player2->Health = GameMode->StartingHealth;
		UpdateHealthUI(Player2->Health, 1);
	}
}

	
///// UI Updating Functions //////
void ADualPlayerController::UpdateHealthUI(int32 NewHealth, int32 PlayerId) {
	HUD->UpdateLifeTotal(NewHealth, PlayerId);
	
}
void ADualPlayerController::UpdateTimeToBeat(FTimespan CurrentBestTime) {
	HUD->UpdateTimeToBeat(CurrentBestTime);
	
}

///// Input Relay functions /////

void ADualPlayerController::JumpPlayer1() {

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Yellow, TEXT("Input recieved"));
	Player1->DoJump();
}
void ADualPlayerController::MovePlayer1(const FInputActionValue& Value) {

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Yellow, TEXT("Input recieved"));
	Player1->Move(Value);
}
void ADualPlayerController::JumpPlayer2() {

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Yellow, TEXT("Input recieved"));
	Player2->DoJump();
}
void ADualPlayerController::MovePlayer2(const FInputActionValue& Value) {

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Yellow, TEXT("Input recieved"));
	Player2->Move(Value);
}
void ADualPlayerController::PauseGame() {

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Yellow, TEXT("Pause Input recieved"));
	GameMode->PauseGame();
}