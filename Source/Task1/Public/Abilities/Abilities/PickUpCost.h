// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "UObject/Object.h"
#include "PickUpCost.generated.h"

/**
 *
 */
UCLASS()
class TASK1_API UPickUpCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	float CalculateBaseMagnitude_Implementation(
		const FGameplayEffectSpec& Spec) const override;
};
