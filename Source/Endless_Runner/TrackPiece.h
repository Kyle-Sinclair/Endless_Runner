// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "TrackPiece.generated.h"

UCLASS()
class ENDLESS_RUNNER_API ATrackPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackPiece();
	ATrackPiece(ATrackPiece* BeforeTrackPiece, ATrackPiece* AfterTrackPiece);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SuperMesh; 

	/*UPROPERTY(VisibleAnywhere)
	class UBoxComponent* ExitCollider; */
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UArrowComponent* TrackSeamPoint;

	/*UPROPERTY()
	TWeakObjectPtr<ATrackPiece> PreviousTrackPiece;*/
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ATrackPiece> PreviousTrackPiece;
	/*UPROPERTY()
	TWeakObjectPtr<ATrackPiece> NextTrackPiece;*/
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ATrackPiece> NextTrackPiece;
	UFUNCTION()
	void DeactivateTrackPiece(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void ActivateTrackPiece();
	

};
