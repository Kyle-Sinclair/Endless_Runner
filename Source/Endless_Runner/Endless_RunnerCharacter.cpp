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

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//OnActorHit.AddDynamic(this, &AEndless_RunnerCharacter::OnBeginOverlap);
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
}

void AEndless_RunnerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	LaneNumber = 1;
	//Add Input Mapping Context

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AEndless_RunnerCharacter::OnCollideWithObstacle);


}

void AEndless_RunnerCharacter::OnCollideWithObstacle(UPrimitiveComponent* /*ignored*/, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Actor Collision"));
	Health--;
	if (Health <= 0) {
		OnKilled.Broadcast(PlayerId);
	}
	OnHealthUpdated.Broadcast(Health, PlayerId);
	OtherActor->Destroy();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AEndless_RunnerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	// Set up action bindings
	//if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
	

}
void AEndless_RunnerCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

}

void AEndless_RunnerCharacter::Move(const FInputActionValue& Value)
{
	
	//Player input testing


	FVector2D MovementVector = Value.Get<FVector2D>();
	LaneNumber += MovementVector.X;
		if (LaneNumber < 0) {
			LaneNumber = 2;
		}
		LaneNumber = LaneNumber % 3;

	FVector newLocation = LaneOffSets[LaneNumber];
	SetActorLocation(newLocation);
}

void AEndless_RunnerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
void AEndless_RunnerCharacter::DoJump() {
	Super::Jump();
}
void AEndless_RunnerCharacter::OnBeginOverlap()
{

}
void AEndless_RunnerCharacter::BindToTrack(TObjectPtr<ATrackManager> OwningTrack) {
	BoundTrack = OwningTrack;

	FVector LaneAdjustment = FVector(0.f,LaneWidth,0.f);
	FVector StartPosition = OwningTrack->GetActorLocation() + FVector(1800.f,LaneWidth,200.f);
	LaneOffSets.Add(StartPosition);
	LaneOffSets.Add(StartPosition + LaneAdjustment);
	LaneOffSets.Add(StartPosition + 2 * LaneAdjustment);
	LaneNumber = 1;
	SetActorLocation(LaneOffSets[LaneNumber]);

}
void AEndless_RunnerCharacter::BindToTrack(TWeakObjectPtr<ATrackManager> OwningTrack) {
	if (OwningTrack.IsValid()) {
		BoundTrack = OwningTrack;

		FVector LaneAdjustment = FVector(0.f, LaneWidth, 0.f);
		FVector StartPosition = OwningTrack->GetActorLocation() + FVector(1800.f, LaneWidth, 200.f);
		LaneOffSets.Add(StartPosition);
		LaneOffSets.Add(StartPosition + LaneAdjustment);
		LaneOffSets.Add(StartPosition + 2 * LaneAdjustment);
		LaneNumber = 1;
		SetActorLocation(LaneOffSets[LaneNumber]);
	}

}

void AEndless_RunnerCharacter::SetPlayerId(int32 Id) {
	PlayerId = Id;
}



