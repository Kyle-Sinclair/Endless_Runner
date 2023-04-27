// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine/GameViewportClient.h"
#include "MPGameViewPortClient.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_RUNNER_API UMPGameViewPortClient : public UGameViewportClient
{
	GENERATED_BODY()
	
public:
	virtual bool InputKey(const FInputKeyEventArgs& inputArgs) override;
};
