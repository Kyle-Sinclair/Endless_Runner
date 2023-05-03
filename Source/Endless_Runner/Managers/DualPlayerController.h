// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Endless_RunnerCharacter.h"

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

	void RegisterPlayer(TObjectPtr<AEndless_RunnerCharacter> Character, int index);
	virtual void BeginPlay() override;
	void SetupPlayerInputComponent();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;
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


};
