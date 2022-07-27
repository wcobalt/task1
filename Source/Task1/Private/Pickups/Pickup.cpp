// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/Pickup.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("Pickup Mesh");
	PickupMesh->SetSimulatePhysics(true);
	PickupMesh->SetupAttachment(RootComponent);
}

void APickup::PostInitProperties()
{
	Super::PostInitProperties();

	if (IsValid(Item) && IsValid(Item->Mesh))
	{
		PickupMesh->SetStaticMesh(Item->Mesh);
	}
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

