// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "LifeTotalWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_RUNNER_API ULifeTotalWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateLifeTotal(int32 newHealth, int32 PlayerId);
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Player1LifeLabel;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Player2LifeLabel;

	


};
