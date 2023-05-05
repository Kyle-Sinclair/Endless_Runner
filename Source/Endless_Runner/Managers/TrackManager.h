// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../TrackPiece.h"
#include "../Obstacle.h"
#include "TrackManager.generated.h"


UCLASS()


class ENDLESS_RUNNER_API ATrackManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackManager();
	~ATrackManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// Obstacle Management /////
	/// <summary>
	/// Returns how much an obstacle should be offset
	/// to transition to the other track
	/// </summary>
	/// <returns></returns>
	FVector GetLocalOffset();
	/// <summary>
	/// Counter for draining obstaces from one track to the other
	/// </summary>
	int32 ObstaclesToPort;
	
public:	
	
	/// Configuration Settngs for BP /////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Track Blueprints")
		TArray<TSubclassOf<ATrackPiece> > PossibleTrackPieces;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Obstacle Blueprints")
		TArray<TSubclassOf<AObstacle>> PossibleObstacles;
	
	UPROPERTY(EditAnywhere)
		int TrackLength;
	UPROPERTY(EditAnywhere)
		float TrackSpeed;
	UPROPERTY(VisibleAnywhere)
		int32 TrackId;
	UPROPERTY(EditDefaultsOnly)
		float TrackDifficulty;
	UPROPERTY(EditAnywhere)
		float PortProbability;

	/// In Game References /////

	UPROPERTY(BlueprintReadOnly)
		TArray<ATrackPiece*> CurrentTrackPieces;
	UPROPERTY(BlueprintReadOnly)
		TArray<TObjectPtr<AObstacle>> CurrentObstacles;
	UPROPERTY()
		TArray<TObjectPtr<AObstacle>> RecievedObstacles;
	UPROPERTY(VisibleAnywhere)
		TWeakObjectPtr<ATrackManager> LinkedTrack;
	UPROPERTY(VisibleAnywhere)
		TWeakObjectPtr<ATrackPiece> HeadTrackPiece;
	UPROPERTY(VisibleAnywhere)
		TWeakObjectPtr<ATrackPiece> TailTrackPiece;
	//Tracks if track has moved far enough to warrant swapping head and tail pieces
	UPROPERTY()
		float TrackDelta; 
	
	
	
	/// <summary>
	/// Track Creation methods called in begin play
	/// </summary>
	UFUNCTION()
	void InitializeTrack();
	UFUNCTION()
	void LinkTrackPieces(); 
	/// <summary>
	/// Track Coniguration methods 
	/// </summary>

	void ConfigureId(const int32 TrackId);
	TArray<FVector> LaneOffsets;

	/// <summary>
	/// Track Management Methods
	/// </summary>
	UFUNCTION()
	void SwapHeadWithTail();
	UFUNCTION()
	void ShiftTrack(float const DeltaTime);
	UFUNCTION()
	void ShiftObstacles(float const DeltaTime);	
	UFUNCTION()
	void ClearObstacles();
	UFUNCTION()
	void PortObstacles();	
	UFUNCTION()
	void RecieveObstacles();
	UFUNCTION()
	void UpdateDifficulty(float const DeltaTime);
	UFUNCTION()
	void ResetProbability();
	UFUNCTION()
	void SpawnObstaclesOnTrack();
	void RecieveTeleportedObstacle(TObjectPtr<AObstacle> ActorToDeposit);

	
	
};
