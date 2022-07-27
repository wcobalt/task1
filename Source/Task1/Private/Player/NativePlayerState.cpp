// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NativePlayerState.h"
#include "Items/Item.h"

void ANativePlayerState::AddItem(UItem* Item)
{
	Inventory.Add(Item);
}

const TArray<UItem*>& ANativePlayerState::GetInventory() const
{
	return Inventory;
}

float ANativePlayerState::CalculateTotalWeight() const
{
	float Result = 0.0f;

	for (auto Item : Inventory)
	{
		Result += Item->Item->Weight;
	}

	return Result;
}
