// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Abilities/PickUpAbility.h"

#include "Hud/NativeHud.h"
#include "Items/Item.h"
#include "Player/NativePlayerController.h"
#include "Player/NativePlayerState.h"

bool UPickUpAbility::CheckCost(
	const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult =  Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags);

	if (!bResult)
	{
		if (auto PlayerController = Cast<ANativePlayerController>(
			ActorInfo->PlayerController.Get()))
		{
			PlayerController->GetNativeHud()->CantFitPickUpEvent();
		}
	}

	return bResult;
}

void UPickUpAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{
	// cost effect doesn't contain how much weight needed
	// it contains how much weight will there be left after the pickup will be
	// picked up. and we need to apply: add effect with just weight of an item

	if (!CostEffect) return;

	if (auto Abilities =
		ActorInfo->AbilitySystemComponent.Get())
	{
		FGameplayEffectContextHandle EffectContext =
					Abilities->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle =
			Abilities->MakeOutgoingSpec(CostEffect,
				1, EffectContext);

		if (SpecHandle.IsValid())
		{
			Abilities->ApplyGameplayEffectSpecToSelf(
				*SpecHandle.Data.Get());
		}
	}
}

void UPickUpAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// check if there's a pickup in sight
	// play sound, take the item, destroy actor

	if (auto Controller = Cast<ANativePlayerController>(
		ActorInfo->PlayerController.Get()))
	{
		if (auto Abilities =
			ActorInfo->AbilitySystemComponent.Get())
		{
			if (auto PickUp = Controller->RetrievePickupInSight())
			{
				UItem* Item = NewObject<UItem>();
				Item->Item = PickUp->Item;
				auto PlayerState =
					Controller->GetPlayerState<ANativePlayerState>();
				PlayerState->AddItem(Item);

				CommitAbility(Handle, ActorInfo, ActivationInfo);
				PickUp->Destroy();

				OnPickedUp(Item);
			}
		}
	}
}
