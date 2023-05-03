// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Engine/EngineTypes.h"
#include "Managers/TrackManager.h"
#include "Endless_RunnerCharacter.generated.h"


UCLASS(config=Game)
class AEndless_RunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* SecondMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;


	UPROPERTY(VisibleAnywhere)
	int32 LaneNumber;	
	UPROPERTY(VisibleAnywhere)
	FVector AnchorPosition;
	UPROPERTY(VisibleAnywhere)

	TWeakObjectPtr<ATrackManager> BoundTrack;



public:
	AEndless_RunnerCharacter();
	void OnBeginOverlap();
	void BindToTrack(TObjectPtr<ATrackManager> OwningTrack);
	void BindToTrack(TWeakObjectPtr<ATrackManager> OwningTrack);

protected:
	UPROPERTY(VisibleAnywhere)

	TArray<FVector> LaneOffSets;

	UPROPERTY(EditDefaultsOnly)
		float LaneWidth = 250.f;


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	UFUNCTION()
	void OnCollideWithObstacle(UPrimitiveComponent* collider, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:

	virtual void Tick(float DeltaSeconds) override;
	void DoJump();
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

