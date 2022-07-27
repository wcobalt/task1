// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Abilities/PickUpCost.h"

#include "Player/NativePlayerController.h"

float UPickUpCost::CalculateBaseMagnitude_Implementation(
	const FGameplayEffectSpec& Spec) const
{
	AActor* Actor = Spec.GetContext().GetInstigator();
	if (auto Controller = Cast<ANativePlayerController>(
		Actor->GetWorld()->GetFirstPlayerController()))
	{
		if (auto PickUp = Controller->RetrievePickupInSight())
		{
			return PickUp->Item->Weight;
		}
	}

	return 0.0f;
}
