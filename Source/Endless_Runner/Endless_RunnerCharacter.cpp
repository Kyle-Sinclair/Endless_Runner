// Copyright Epic Games, Inc. All Rights Reserved.

#include "Endless_RunnerCharacter.h"
#include "Endless_RunnerGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Managers/TrackManager.h"

#include "EnhancedInputSubsystems.h"




//////////////////////////////////////////////////////////////////////////
// AEndless_RunnerCharacter

AEndless_RunnerCharacter::AEndless_RunnerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	
	
}

void AEndless_RunnerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	LaneNumber = 1;

	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AEndless_RunnerCharacter::OnCollideWithObstacle);
}

/// <summary>
/// Takes damage on this character, destroys the obstacle it collided with and broadcasts relevant delegates
/// </summary>
/// <param name=""></param>
/// <param name="OtherActor"></param>
/// <param name="OtherComp"></param>
/// <param name="OtherIndex"></param>
/// <param name="bFromSweep"></param>
/// <param name="SweepResult"></param>
void AEndless_RunnerCharacter::OnCollideWithObstacle(UPrimitiveComponent* /*ignored*/, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Health--;
	if (Health <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Character is Dead"));
		OnKilled.Broadcast(PlayerId);
	}
	OnHealthUpdated.Broadcast(Health, PlayerId);
	OnTakenDamage.Broadcast();
	OtherActor->Destroy();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AEndless_RunnerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
}
void AEndless_RunnerCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

/// <summary>
/// Recieves input values from DualPLayerController
/// and snaps character to lane based on that
/// </summary>
/// <param name="Value"></param>
void AEndless_RunnerCharacter::Move(const FInputActionValue& Value)
{
	if (GetCharacterMovement()->IsMovingOnGround()) {
		FVector2D MovementVector = Value.Get<FVector2D>();
		LaneNumber += MovementVector.X;
		if (LaneNumber < 0) {
			LaneNumber = 2;
		}
		LaneNumber = LaneNumber % 3;

		FVector newLocation = LaneOffSets[LaneNumber];
		SetActorLocation(newLocation);
	}
}

void AEndless_RunnerCharacter::DoJump() {
	Super::Jump();
}

/// <summary>
/// Configuration method that allows track to provide information about lane
/// sizes and positions to the character
/// </summary>
/// <param name="OwningTrack"></param>
void AEndless_RunnerCharacter::BindToTrack(TObjectPtr<ATrackManager> OwningTrack) {
	BoundTrack = OwningTrack;

	FVector LaneAdjustment = FVector(0.f,LaneWidth,0.f);
	FVector StartPosition = OwningTrack->GetActorLocation() + FVector(900.f,LaneWidth,200.f);
	LaneOffSets.Add(StartPosition);
	LaneOffSets.Add(StartPosition + LaneAdjustment);
	LaneOffSets.Add(StartPosition + 2 * LaneAdjustment);
	LaneNumber = 1;
	SetActorLocation(LaneOffSets[LaneNumber]);
	OnTakenDamage.AddDynamic(OwningTrack, &ATrackManager::ResetProbability);

}

/// <summary>
/// Configured at set up
/// Has same value as iot's bound track manager's entry in
/// the game instance. 
/// </summary>
/// <param name="Id"></param>
void AEndless_RunnerCharacter::SetPlayerId(int32 Id) {
	PlayerId = Id;
}



