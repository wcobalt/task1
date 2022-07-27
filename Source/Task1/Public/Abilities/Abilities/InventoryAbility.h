// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/NativeGameplayAbility.h"
#include "UObject/Object.h"
#include "InventoryAbility.generated.h"

/**
 *
 */
UCLASS()
class TASK1_API UInventoryAbility : public UNativeGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag OpenedInventoryEffectTag;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> OpenedInventoryEffect;

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
};
