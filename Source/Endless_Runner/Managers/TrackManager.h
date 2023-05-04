// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../TrackPiece.h"
#include "../Factories/ObstacleFactory.h"
#include "TrackManager.generated.h"
USTRUCT()
		struct FObstacleCollection
	{
		GENERATED_BODY()
	public:
		UPROPERTY()
		TArray<TSubclassOf<AObstacle>> ObstacleCollection;

		FObstacleCollection() {
			ObstacleCollection.Reserve(9);
		}
	};
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Track Blueprints")
	TArray<TSubclassOf<ATrackPiece> > PossibleTrackPieces;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Obstacle Blueprints")
	TArray<TSubclassOf<AObstacle>> PossibleObstacles;
	

	UPROPERTY(EditAnywhere)
	TSubclassOf<UObstacleFactory> ObstacleFactory;

	UPROPERTY()
	TObjectPtr<UObstacleFactory> ObstacleFactoryRef;
	UPROPERTY(BlueprintReadOnly)
	TArray<ATrackPiece*> CurrentTrackPieces;
	UPROPERTY(EditAnywhere)
	int TrackLength;
	UPROPERTY(EditAnywhere) 
	float TrackSpeed;
	
	UPROPERTY()
	float TrackDelta; 
	UPROPERTY( EditAnywhere)
	float TrackDifficulty;
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ATrackPiece> HeadTrackPiece; 
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
	void UpdateDifficulty(float const DeltaTime);
	UFUNCTION()
	void SpawnObstaclesOnTrack();
	TArray<FVector> LaneOffsets;
	
	
private:
	void RemoveTrackObstacles(TWeakObjectPtr<ATrackPiece> TailTrackPiece);
};
