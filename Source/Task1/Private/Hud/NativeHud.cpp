// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/NativeHud.h"

#include "Engine/Canvas.h"

ANativeHud::ANativeHud()
{
	PrimaryActorTick.bCanEverTick = false;
}

UInventoryWidget* ANativeHud::GetInventoryWidget()
{
	return InventoryWidget;
}

UMainPlayerUi* ANativeHud::GetMainPlayerUi()
{
	return MainPlayerUi;
}

void ANativeHud::CantFitPickUpEvent()
{
	CurrentCrosshairColor = CrosshairColorWhenCantFit;

	GetWorldTimerManager().ClearTimer(CantFitTimerHandle);
	GetWorldTimerManager().SetTimer(CantFitTimerHandle,
	 [this]()
	 {
		CurrentCrosshairColor = CrosshairColor;
	 },
	 CantFitEffectDuration, false);
}

void ANativeHud::ShowHud()
{
	bDoShowCrosshair = true;

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (Controller)
	{
		Controller->bShowMouseCursor = false;
		Controller->bEnableClickEvents = false;
		Controller->bEnableMouseOverEvents = false;
	}

	if (MainPlayerUi)
	{
		MainPlayerUi->SetVisibility(ESlateVisibility::Visible);
	}
}

void ANativeHud::HideHud()
{
	bDoShowCrosshair = false;

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (Controller)
	{
		Controller->bShowMouseCursor = true;
		Controller->bEnableClickEvents = true;
		Controller->bEnableMouseOverEvents = true;
	}

	if (MainPlayerUi)
	{
		MainPlayerUi->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ANativeHud::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerUi = CreateWidget<UMainPlayerUi>(GetWorld(),
		MainPlayerUiClass);
	MainPlayerUi->AddToViewport(0);

	InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(),
		InventoryWidgetClass);
	InventoryWidget->CloseInventory();
	InventoryWidget->AddToViewport(1);
}

void ANativeHud::DrawHUD()
{
	Super::DrawHUD();

	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	if (bDoShowCrosshair)
	{
		DrawLine(Center.X - CrosshairSize.X / 2,
			Center.Y - CrosshairSize.Y / 2,
			Center.X + CrosshairSize.X / 2,
			Center.Y + CrosshairSize.Y / 2, CurrentCrosshairColor);
		DrawLine(Center.X - CrosshairSize.X / 2,
			Center.Y + CrosshairSize.Y / 2,
			Center.X + CrosshairSize.X / 2,
			Center.Y - CrosshairSize.Y / 2, CurrentCrosshairColor);
	}
}
