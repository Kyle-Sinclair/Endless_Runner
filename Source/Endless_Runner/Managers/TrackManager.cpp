// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackManager.h"

// Sets default values
ATrackManager::ATrackManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ExitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Exit Collider"));

}

// Called when the game starts or when spawned
void ATrackManager::BeginPlay()
{
	Super::BeginPlay();
	ExitCollider->OnComponentBeginOverlap.AddDynamic(this, &ATrackManager::ExtendTrack);
}

// Called every frame
void ATrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrackManager::ExtendTrack(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Track being Extended"));
	}
}

