// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Obstacle.h"
#include "Engine/StaticMesh.h"
#include "ObstacleFactory.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ENDLESS_RUNNER_API UObstacleFactory : public UObject
{
	GENERATED_BODY()

private:
protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<UStaticMesh>> SpawnableObstacles;

public:
	UObstacleFactory();
	void ExampleFunction();
};
