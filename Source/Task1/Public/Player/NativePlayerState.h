// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NativePlayerState.generated.h"

class UItem;

UCLASS()
class TASK1_API ANativePlayerState : public APlayerState
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UItem*> Inventory;

public:
	UFUNCTION(BlueprintCallable)
	void AddItem(UItem* Item);

	UFUNCTION(BlueprintCallable)
	const TArray<UItem*>& GetInventory() const;

	UFUNCTION(BlueprintCallable)
	float CalculateTotalWeight() const;
};
