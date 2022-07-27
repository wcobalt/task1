// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Abilities/PickUpCostCheck.h"

#include "Abilities/CharacterAttributeSet.h"
#include "Player/NativePlayerController.h"
#include "Items/Item.h"

UPickUpCostCheck::UPickUpCostCheck()
{
	WeightDef.AttributeToCapture = UCharacterAttributeSet::GetWeightAttribute();
	WeightDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	WeightDef.bSnapshot = false;

	MaxWeightDef.AttributeToCapture =
		UCharacterAttributeSet::GetMaxWeightAttribute();
	MaxWeightDef.AttributeSource =
		EGameplayEffectAttributeCaptureSource::Source;
	MaxWeightDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(WeightDef);
	RelevantAttributesToCapture.Add(MaxWeightDef);
}

float UPickUpCostCheck::CalculateBaseMagnitude_Implementation(
	const FGameplayEffectSpec& Spec) const
{
	AActor* Actor = Spec.GetContext().GetInstigator();
	if (auto Controller = Cast<ANativePlayerController>(
		Actor->GetWorld()->GetFirstPlayerController()))
	{
		if (auto PickUp = Controller->RetrievePickupInSight())
		{
			FAggregatorEvaluateParameters EvaluationParameters;

			float MaxWeight = 0.0f;
			float Weight = 0.0f;
			GetCapturedAttributeMagnitude(MaxWeightDef, Spec,
				EvaluationParameters, MaxWeight);
			GetCapturedAttributeMagnitude(WeightDef, Spec,
				EvaluationParameters, Weight);

			float Value = MaxWeight - PickUp->Item->Weight - 2 * Weight;
			return Value;
		}
	}

	return 0.0f;
}
