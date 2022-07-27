// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemDataAsset.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class TASK1_API APickup : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UItemDataAsset* Item;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PickupMesh;

	APickup();

	virtual void PostInitProperties() override;

	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
};
