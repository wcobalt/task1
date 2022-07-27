// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Abilities/InventoryAbility.h"

#include "AbilitySystemComponent.h"
#include "Hud/NativeHud.h"
#include "Player/NativePlayerController.h"

void UInventoryAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
	FGameplayTagContainer Container;
	Container.AddTag(OpenedInventoryEffectTag);

	if (auto Abilities =
		ActorInfo->AbilitySystemComponent.Get())
	{
		bool bIsOpened =
			(Abilities->GetActiveEffectsWithAllTags(Container).Num() != 0);

		if (auto Controller = Cast<ANativePlayerController>(
			ActorInfo->PlayerController.Get()))
		{
			if (bIsOpened)
			{
				// close
				Abilities->RemoveActiveEffectsWithTags(Container);
				Controller->GetNativeHud()->ShowHud();
				Controller->GetNativeHud()->GetInventoryWidget()
					->CloseInventory();
			}
			else
			{
				// open
				FGameplayEffectContextHandle EffectContext =
					Abilities->MakeEffectContext();
				EffectContext.AddSourceObject(this);

				FGameplayEffectSpecHandle SpecHandle =
					Abilities->MakeOutgoingSpec(OpenedInventoryEffect,
						1, EffectContext);

				if (SpecHandle.IsValid())
				{
					Abilities->ApplyGameplayEffectSpecToSelf(
						*SpecHandle.Data.Get());
				}
				Controller->GetNativeHud()->HideHud();
				Controller->GetNativeHud()->GetInventoryWidget()
					->ShowInventory();
			}
		}
	}
}
