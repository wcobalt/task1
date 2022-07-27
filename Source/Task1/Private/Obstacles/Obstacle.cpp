// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Obstacle.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = false;

	ObstacleMesh =
		CreateDefaultSubobject<UStaticMeshComponent>("Obstacle Mesh");
	ObstacleMesh->SetupAttachment(RootComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();

}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

