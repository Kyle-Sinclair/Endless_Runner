// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Endless_RunnerGameMode.h"
#include "GameFramework/Pawn.h"

#include "Components/InputComponent.h"
#include "DualPlayerController.h"


ADualPlayerController::ADualPlayerController() {
	InputComponent = CreateDefaultSubobject<UInputComponent>("Input Component");

}

void ADualPlayerController::BeginPlay()
{
	// Call the base class  
	//Add Input Mapping Context

	
		int32 id = GetLocalPlayer()->GetControllerId();
		UE_LOG(LogTemp, Warning, TEXT("PLayer Controller pointer was valid for controller id %i"), id);

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	
	AEndless_RunnerGameMode* mymode = Cast<AEndless_RunnerGameMode>(GetWorld()->GetAuthGameMode());
	
		SetupPlayerInputComponent();

}

void ADualPlayerController::RegisterPlayer(TObjectPtr<AEndless_RunnerCharacter> NewCharacter, int index) {
	if (index == 0) {
		Player1 = NewCharacter;
	}
	else {
		Player2 = NewCharacter;
	}
}
	

void ADualPlayerController::SetupPlayerInputComponent()
{
	
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->FindComponentByClass<UEnhancedInputComponent>());

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ADualPlayerController::JumpPlayer1);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADualPlayerController::MovePlayer1);
	EnhancedInputComponent->BindAction(JumpAction2, ETriggerEvent::Completed, this, &ADualPlayerController::JumpPlayer2);
	EnhancedInputComponent->BindAction(MoveAction2, ETriggerEvent::Triggered, this, &ADualPlayerController::MovePlayer2);

}

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