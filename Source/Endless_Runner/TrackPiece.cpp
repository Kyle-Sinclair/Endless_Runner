// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackPiece.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
ATrackPiece::ATrackPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	ExitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Exit Collider"));
}

// Called when the game starts or when spawned
void ATrackPiece::BeginPlay()
{
	Super::BeginPlay();
	ExitCollider->OnComponentBeginOverlap.AddDynamic(this, &ATrackPiece::DeactivateTrackPiece);


}

// Called every frame
void ATrackPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrackPiece::DeactivateTrackPiece(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();

}

void ATrackPiece::ActivateTrackPiece() {

}
