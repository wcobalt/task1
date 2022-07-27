// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.generated.h"

UCLASS(BlueprintType)
class TASK1_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundWave* PickUpSound;
};
