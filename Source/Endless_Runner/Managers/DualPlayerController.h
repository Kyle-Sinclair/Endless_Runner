// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Endless_RunnerCharacter.h"
#include "../UI/LifeTotalWidget.h"
#include "../UI/HUDWidget.h"
#include "Misc/Timespan.h"

#include "DualPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_RUNNER_API ADualPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	ADualPlayerController();
	UFUNCTION()
	void MovePlayer1(const FInputActionValue& Value);
	UFUNCTION()
	void MovePlayer2(const FInputActionValue& Value);
	UFUNCTION()
	void JumpPlayer1();
	UFUNCTION()
	void JumpPlayer2();
	UFUNCTION()
	void PauseGame();
	UFUNCTION()
	void UpdateHealthUI(int32 NewHealth, int32 PlayerId);	
	UFUNCTION()
	void UpdateTimeToBeat(FTimespan CurrentBestTime);
	
	void RegisterPlayer(TObjectPtr<AEndless_RunnerCharacter> Character, int index);
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaSeconds) override;
	void SetupPlayerInputComponent();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = UI, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UHUDWidget> HUDImplementation;
	

	UPROPERTY()
	TObjectPtr<UHUDWidget> HUD;
	UPROPERTY()
	TObjectPtr<class AEndless_RunnerGameMode> GameMode;
	UPROPERTY(VisibleAnywhere,  meta = (AllowPrivateAccess = "true"))
		TObjectPtr<AEndless_RunnerCharacter> Player1;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<AEndless_RunnerCharacter> Player2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PauseAction;


	
};
