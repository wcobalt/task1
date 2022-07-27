// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/MainPlayerUi.h"

#include "Pickups/Pickup.h"
#include "Player/NativePlayerCharacter.h"
#include "Player/NativePlayerController.h"

void UMainPlayerUi::SetPickupInSight(TWeakObjectPtr<APickup> Pickup)
{
	PickupInSight = Pickup;

	OnPickupSet.Broadcast();
}

APickup* UMainPlayerUi::GetPickupInSight() const
{
	return PickupInSight.Get();
}

FString UMainPlayerUi::GetHintForCrosshair() const
{
	if (PickupInSight.IsValid())
	{
		// todo: move to text and FormatText
		return PickupInSight->Item->DisplayName.ToString() + " [" +
			FString::Printf(TEXT("%.1f"), PickupInSight->Item->Weight) +
				"]";
	}

	return {};
}

float UMainPlayerUi::GetCurrentWeight() const
{
	if (auto Character = GetCharacter())
	{
		return Character->AttributeSet->GetWeight();
	}

	return 0.0f;
}

float UMainPlayerUi::GetMaxWeight() const
{
	if (auto Character = GetCharacter())
	{
		return Character->AttributeSet->GetMaxWeight();
	}

	return 0.0f;
}

ANativePlayerCharacter* UMainPlayerUi::GetCharacter() const
{
	return Cast<ANativePlayerController>(GetWorld()
		->GetFirstPlayerController())->GetNativePlayerCharacter();
}
