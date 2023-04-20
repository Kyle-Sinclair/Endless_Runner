// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Obstacle.generated.h"

UCLASS()
class ENDLESS_RUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ObstacleMesh; 

	UPROPERTY(EditAnywhere)
	UBoxComponent* ObstacleCollider;
	virtual void Tick(float DeltaTime) override;
	void ConfigureMesh(UStaticMesh newMesh);
	void ConfigureCollider(FVector ColliderParameters);
	void Recycle();
	void SetPosition();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
	
};
