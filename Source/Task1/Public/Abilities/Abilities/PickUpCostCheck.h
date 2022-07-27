// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "UObject/Object.h"
#include "PickUpCostCheck.generated.h"

/**
 *
 */
UCLASS()
class TASK1_API UPickUpCostCheck : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UPickUpCostCheck();

	float CalculateBaseMagnitude_Implementation(
		const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition WeightDef;
	FGameplayEffectAttributeCaptureDefinition MaxWeightDef;
};
