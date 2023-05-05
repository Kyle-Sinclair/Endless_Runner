// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../TrackPiece.h"
#include "../Factories/ObstacleFactory.h"
#include "TrackManager.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTeleportObstacle, AActor*, ObstacleToTeleport, int32, TrackId);

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
	FVector GetLocalOffset();
	int32 ObstaclesToPort;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Track Blueprints")
	TArray<TSubclassOf<ATrackPiece> > PossibleTrackPieces;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Obstacle Blueprints")
	TArray<TSubclassOf<AObstacle>> PossibleObstacles;
	
	UPROPERTY()
	FTeleportObstacle OnTeleportObstacle;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UObstacleFactory> ObstacleFactory;

	UPROPERTY()
	TObjectPtr<UObstacleFactory> ObstacleFactoryRef;
	UPROPERTY(BlueprintReadOnly)
	TArray<ATrackPiece*> CurrentTrackPieces;
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AObstacle>> CurrentObstacles;
	UPROPERTY()
	TArray<TObjectPtr<AObstacle>> RecievedObstacles;
	UPROPERTY(EditAnywhere)
	int TrackLength;
	UPROPERTY(EditAnywhere) 
	float TrackSpeed;
	UPROPERTY(VisibleAnywhere) 
	int32 TrackId;
	
	UPROPERTY()
	float TrackDelta; 
	UPROPERTY( EditAnywhere)
	float TrackDifficulty;
	UPROPERTY( EditAnywhere)
	float PortProbability;
	UPROPERTY( EditAnywhere)
	int32 PortDepth;
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ATrackManager> LinkedTrack;
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ATrackPiece> HeadTrackPiece;
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ATrackPiece> PlayerTrackPiece; 
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ATrackPiece> TailTrackPiece;
	
	
	UFUNCTION()
	void InitializeTrack();
	UFUNCTION()
	void LinkTrackPieces(); 
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
	TArray<FVector> LaneOffsets;
	
	void ConfigureId(const int32 TrackId);
private:
	void RemoveTrackObstacles(TWeakObjectPtr<ATrackPiece> TailTrackPiece);
};
