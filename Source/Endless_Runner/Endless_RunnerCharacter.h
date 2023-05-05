// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Engine/EngineTypes.h"
#include "Managers/TrackManager.h"
#include "Endless_RunnerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateHealthDelegate, int32, Health, int32, PlayerID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakenDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnnounceKilledDelegate, int32, Health);


UCLASS(config=Game)
class AEndless_RunnerCharacter : public ACharacter
{
	GENERATED_BODY()


	


public:
	AEndless_RunnerCharacter();

	///// Configurations Methods /////
	void BindToTrack(TObjectPtr<ATrackManager> OwningTrack);
	void SetPlayerId(int32 Id);
	///// Delegates for reporting to interested systems /////
	UPROPERTY()
		FUpdateHealthDelegate OnHealthUpdated;
	UPROPERTY()
		FAnnounceKilledDelegate OnKilled;
	UPROPERTY()
		FTakenDamage OnTakenDamage;
	UPROPERTY(VisibleAnywhere)
		int32 Health;

protected:
	///// Personal Data Methods /////

	UPROPERTY(VisibleAnywhere)
		int32 LaneNumber;
	UPROPERTY(VisibleAnywhere)
		TWeakObjectPtr<ATrackManager> BoundTrack;

	UPROPERTY()
		TArray<FVector> LaneOffSets;
	UPROPERTY(EditDefaultsOnly)
		float LaneWidth = 250.f;
	
		int32 PlayerId;

	///// Overridden methods from base class /////


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/// <summary>
	/// Does binding of impact collusion to capsule component
	/// </summary>
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	/// <summary>
	/// Destroy obstacles method
	/// </summary>
	UFUNCTION()
	void OnCollideWithObstacle(UPrimitiveComponent* collider, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:

	void DoJump();
	/** Called for movement input */
	void Move(const FInputActionValue& Value);


};

