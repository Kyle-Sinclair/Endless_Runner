// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackPiece.h"
#include "Components/StaticMeshComponent.h"
#include "Obstacle.h"
#include "DrawDebugHelpers.h"

#include "Components/BoxComponent.h"
// Sets default values
ATrackPiece::ATrackPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	SetRootComponent(SuperMesh);
	SetActorEnableCollision(false);
	//SuperMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Ignore);
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
	//Example

}

// Called when the game starts or when spawned
void ATrackPiece::BeginPlay()
{
	Super::BeginPlay();
	
	TrackSeamPoint->SetWorldLocation(GetActorLocation() + FVector(900.f, 0.f, 0.f));
	//ExitCollider->OnComponentBeginOverlap.AddDynamic(this, &ATrackPiece::DeactivateTrackPiece);
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Track piece created"));
	}

	

}



void ATrackPiece::Tick(float DeltaTime)
{
	/*AEndless_RunnerGameMode* mymode = Cast<AEndless_RunnerGameMode>(GetWorld()->GetAuthGameMode());
	FVector BoxSize = FVector(50.f, 50.f, 50.f);

	TArray<FVector> ObstacleRelativeOffsets = mymode->ObstacleRelativeOffsets;

	for (FVector vec : ObstacleRelativeOffsets)
	{
		DrawDebugSolidBox(GetWorld(), TrackSeamPoint->GetComponentLocation() - vec, BoxSize, FColor::Blue, false);
	}*/
	/*FVector obstacleLeftLaneFirst = TrackSeamPoint->GetComponentLocation() - FVector(250.f, -150.f, -150.f);
	FVector BoxSize = FVector(50.f, 50.f, 50.f);

	DrawDebugSolidBox(GetWorld(), obstacleLeftLaneFirst, BoxSize, FColor::Blue, false);
	FVector obstacleLeftLaneSecond = TrackSeamPoint->GetComponentLocation() - FVector(550.f, -150.f, -150.f);

	DrawDebugSolidBox(GetWorld(), obstacleLeftLaneSecond, BoxSize, FColor::Red, false);
	FVector obstacleLeftLaneThird = TrackSeamPoint->GetComponentLocation() - FVector(850.f, -150.f, -150.f);

	DrawDebugSolidBox(GetWorld(), obstacleLeftLaneThird, BoxSize, FColor::Green, false);*/
}

void ATrackPiece::DeactivateTrackPiece(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();

}

void ATrackPiece::ActivateTrackPiece() {

}

void ATrackPiece::AttachObstacleToTrackPiece(const FVector SpawnPosition, AObstacle* ObstacleToWeld)
{

//	AEndless_RunnerGameMode* mymode = Cast<AEndless_RunnerGameMode>(GetWorld()->GetAuthGameMode());
//	FVector BoxSize = FVector(50.f, 50.f, 50.f);
//
//	TArray<FVector> ObstacleRelativeOffsets = mymode->ObstacleRelativeOffsets;
//	for (FVector vec : ObstacleRelativeOffsets)
//	{
		Obstacles.Add(ObstacleToWeld);
		//ObstacleToWeld->SetActorLocation(TrackSeamPoint - SpawnPosition);
		ObstacleToWeld->AttachToActor(this,FAttachmentTransformRules::KeepWorldTransform);
//		//DrawDebugSolidBox(GetWorld(), TrackSeamPoint->GetComponentLocation() - vec, BoxSize, FColor::Blue, false);
//	}
}
