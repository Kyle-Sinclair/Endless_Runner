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
	SetRootComponent(SuperMesh);
	TrackSeamPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Track Seam Point"));
	TrackSeamPoint->AttachToComponent(SuperMesh, FAttachmentTransformRules::KeepRelativeTransform);
}
ATrackPiece::ATrackPiece(ATrackPiece* BeforeTrackPiece, ATrackPiece* AfterTrackPiece)
{
	//PrimaryActorTick.bCanEverTick = true;
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	SetRootComponent(SuperMesh);
	TrackSeamPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Track Seam Point"));
	TrackSeamPoint->AttachToComponent(SuperMesh, FAttachmentTransformRules::KeepRelativeTransform);

	PreviousTrackPiece = BeforeTrackPiece;
	NextTrackPiece = AfterTrackPiece;

}

// Called when the game starts or when spawned
void ATrackPiece::BeginPlay()
{
	Super::BeginPlay();
	TrackSeamPoint->SetWorldLocation(GetActorLocation() + FVector(1200.f, 0.f, 0.f));
	//ExitCollider->OnComponentBeginOverlap.AddDynamic(this, &ATrackPiece::DeactivateTrackPiece);
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Track piece created"));
	}

}



void ATrackPiece::DeactivateTrackPiece(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();

}

void ATrackPiece::ActivateTrackPiece() {

}