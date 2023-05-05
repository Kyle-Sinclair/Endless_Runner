// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackPiece.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ATrackPiece::ATrackPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	SetRootComponent(SuperMesh);
	SetActorEnableCollision(false);
	TrackSeamPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Track Seam Point"));
	TrackSeamPoint->AttachToComponent(SuperMesh, FAttachmentTransformRules::KeepRelativeTransform);
}
ATrackPiece::ATrackPiece(ATrackPiece* BeforeTrackPiece, ATrackPiece* AfterTrackPiece)
{
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	SetRootComponent(SuperMesh);
	TrackSeamPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Track Seam Point"));
	TrackSeamPoint->AttachToComponent(SuperMesh, FAttachmentTransformRules::KeepRelativeTransform);
	PreviousTrackPiece = BeforeTrackPiece;
	NextTrackPiece = AfterTrackPiece;
}

void ATrackPiece::BeginPlay()
{
	Super::BeginPlay();
	InitializeObstacleOffsets();
	TrackSeamPoint->SetWorldLocation(GetActorLocation() + FVector(900.f, 0.f, 0.f));
}

void ATrackPiece::DeactivateTrackPiece(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}

void ATrackPiece::ActivateTrackPiece() {

}

void ATrackPiece::InitializeObstacleOffsets() {
	ObstacleRelativeOffsets.Add(FVector(250.f, -200.f, -100.f));
	ObstacleRelativeOffsets.Add(FVector(550.f, -200.f, -100.f));
	ObstacleRelativeOffsets.Add(FVector(850.f, -200.f, -100.f));
	ObstacleRelativeOffsets.Add(FVector(250.f, -400.f, -100.f));
	ObstacleRelativeOffsets.Add(FVector(550.f, -400.f, -100.f));
	ObstacleRelativeOffsets.Add(FVector(850.f, -400.f, -100.f));
	ObstacleRelativeOffsets.Add(FVector(250.f, -600.f, -100.f));
	ObstacleRelativeOffsets.Add(FVector(550.f, -600.f, -100.f));
	ObstacleRelativeOffsets.Add(FVector(850.f, -600.f, -100.f));
}