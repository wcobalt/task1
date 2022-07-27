// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/NativeGameplayAbility.h"
#include "Items/Item.h"
#include "Sound/SoundCue.h"
#include "PickUpAbility.generated.h"

/**
 *
 */
UCLASS()
class TASK1_API UPickUpAbility : public UNativeGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> CostEffect;

	bool CheckCost(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		FGameplayTagContainer* OptionalRelevantTags) const override;

	void ApplyCost(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) const override;

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPickedUp(UItem* Item);
};
