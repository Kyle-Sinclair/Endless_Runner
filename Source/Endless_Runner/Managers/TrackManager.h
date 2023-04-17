// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../TrackPiece.h"
#include "TrackManager.generated.h"

UCLASS()
class ENDLESS_RUNNER_API ATrackManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* ExitCollider; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Track Blueprints")
	TArray<TSubclassOf<ATrackPiece> > PossibleTrackPieces;
		
	UPROPERTY()
	TArray<ATrackPiece*> CurrentTrackPieces;
	UPROPERTY()
	int32 TrackCount; 
	UPROPERTY(EditAnywhere) 
	float TrackSpeed;
	
	UPROPERTY()
	float TrackDelta;
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ATrackPiece> HeadTrackPiece; 
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ATrackPiece> TailTrackPiece;
	
	
	UFUNCTION()
	void InitializeTrack();
	UFUNCTION()
	void LinkTrackPieces(); 
	UFUNCTION()
	void ShiftTrack(float const DeltaTime);

};
