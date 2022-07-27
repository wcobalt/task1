// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/NativePlayerCharacter.h"
#include "UObject/Object.h"
#include "MainPlayerUi.generated.h"

class APickup;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickupSet);

UCLASS()
class TASK1_API UMainPlayerUi : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPickupSet OnPickupSet;

	void SetPickupInSight(TWeakObjectPtr<APickup> Pickup);

	UFUNCTION(BlueprintCallable)
	APickup* GetPickupInSight() const;

	UFUNCTION(BlueprintCallable)
	FString GetHintForCrosshair() const;
protected:
	UFUNCTION(BlueprintCallable)
	float GetCurrentWeight() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxWeight() const;

	ANativePlayerCharacter* GetCharacter() const;
private:
	TWeakObjectPtr<APickup> PickupInSight;
};
