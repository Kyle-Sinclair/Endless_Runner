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
	SetObstacleMapSize();
	TrackSeamPoint->SetWorldLocation(GetActorLocation() + FVector(900.f, 0.f, 0.f));
}


/*void ATrackPiece::Tick(float DeltaTime)
{
	
}*/

void ATrackPiece::DeactivateTrackPiece(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();

}

void ATrackPiece::ActivateTrackPiece() {

}
void ATrackPiece::MapObstacleToTrackPiece(const int32 ObstacleMapping, const FVector SpawnPosition, AObstacle* ObstacleToWeld) {

	
}
void ATrackPiece::AttachObstacleToTrackPiece(const FVector SpawnPosition, AObstacle* ObstacleToWeld)
{
	Obstacles.Add(ObstacleToWeld);
	ObstacleToWeld->AttachToActor(this,FAttachmentTransformRules::KeepWorldTransform);

}
void ATrackPiece::SetObstacleMapSize() {

	for (int i = 0; i < ObstacleMappingSize; i++) {
		ObstacleMap.Emplace(i, nullptr);
	}
}

bool ATrackPiece::HasObstacles() {
	return Obstacles.Num()>0;
}
void ATrackPiece::PortObstacle(const int32 DepthCount) {
	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("Attempting Port"));

	if (DepthCount <= 0) {
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("Port Depth Count reached"));

		return;
	}

	if (!HasObstacles()) {
		NextTrackPiece->PortObstacle(DepthCount - 1);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("Skipping Port"));

	}
	else {

		AActor* ObstacleToPort = SelectRandomObstacle();
		if (ObstacleToPort->IsValidLowLevel()) {

			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Red, TEXT("PORTING"));

			FVector ObstacleRelativeTransform = ObstacleToPort->GetActorLocation();
			//GetActorTransform().GetRelativeTransform();
		//FVector ObstacleRelativeLocation = ObstacleRelativeTransform.GetLocation();

			ObstacleToPort->Destroy();

			LinkedTrackPiece->DepositObstacle(ObstacleRelativeTransform);
		}
	}
}

void ATrackPiece::RemoveOneObstacle(const int32 DepthCount) {
	if (DepthCount <= 0) {
		return;
	}
	if (!HasObstacles()) {
		NextTrackPiece->RemoveOneObstacle(DepthCount - 1);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15.f, FColor::Green, TEXT("Removing Obstacle"));
	}
	AActor* ObstacleToDestroy = SelectRandomObstacle();
	if (ObstacleToDestroy) {
		ObstacleToDestroy->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Obstacles.Remove(Cast<AObstacle>(ObstacleToDestroy));
		ObstacleToDestroy->Destroy();
	}

}

void ATrackPiece::DepositObstacle( FVector RelativeLocation) {
	//ObstacleToDeposit->SetActorRelativeLocation(RelativeLocation);
	AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(PossibleObstacles[0],RelativeLocation, GetActorRotation());
	//FHitResult result;
	//ObstacleToDeposit->SetActorLocation(FVector(0.f, 0.f, 500.f), false, &result, ETeleportType::None);
	AttachObstacleToTrackPiece(TrackSeamPoint->GetComponentLocation() + RelativeLocation, Obstacle);
	//Obstacle->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

}
AActor* ATrackPiece::SelectRandomObstacle() {
	const int32 index = FMath::FRandRange(0, Obstacles.Num());
	if (index > 0) {
		return Obstacles[index];
	}
	return nullptr;
	/*TArray<AActor*> AttachedObstacles;
	GetAttachedActors(AttachedObstacles);
	const int32 index = FMath::FRandRange(0, AttachedObstacles.Num());
	if (index > 0 && AttachedObstacles[index]->IsValidLowLevel()) {
		Obstacles.Remove(Cast<AObstacle>(AttachedObstacles[index]));
		return AttachedObstacles[index];

	}
	return nullptr;*/
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