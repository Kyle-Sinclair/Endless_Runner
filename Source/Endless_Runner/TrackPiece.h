// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TrackPiece.generated.h"

UCLASS()
class ENDLESS_RUNNER_API ATrackPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SuperMesh; 

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* ExitCollider;

	UFUNCTION()
	void DeactivateTrackPiece(); 
	UFUNCTION()
	void ActivateTrackPiece();

};
