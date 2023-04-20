// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Track Seam Point"));
	ObstacleCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("My Super Mesh"));
	ObstacleCollider->SetupAttachment(RootComponent);
	ObstacleMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}	

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AObstacle::ConfigureMesh(UStaticMesh newMesh) {

}

void AObstacle::ConfigureCollider(FVector ColliderParameters)
{

}

void AObstacle::Recycle()
{

}

void AObstacle::SetPosition()
{

}

