// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "UObject/Object.h"
#include "CharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(Class, Property)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(Class, Property)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Property)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Property)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Property)

UCLASS()
class TASK1_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UCharacterAttributeSet();

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Weight;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Weight);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxWeight;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxWeight);
};
