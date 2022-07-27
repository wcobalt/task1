// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemDataAsset.h"
#include "Item.generated.h"

UCLASS(BlueprintType)
class TASK1_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UItemDataAsset* Item;

	UItem();
};
