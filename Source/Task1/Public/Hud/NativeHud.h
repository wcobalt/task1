// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidget.h"
#include "MainPlayerUi.h"
#include "GameFramework/HUD.h"
#include "NativeHud.generated.h"

UCLASS()
class TASK1_API ANativeHud : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass =
		UInventoryWidget::StaticClass();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainPlayerUi> MainPlayerUiClass =
		UMainPlayerUi::StaticClass();

	UPROPERTY(EditAnywhere)
	FLinearColor CrosshairColor = FLinearColor::White;

	UPROPERTY(EditAnywhere)
	float CantFitEffectDuration = 0.5f;

	UPROPERTY(EditAnywhere)
	FLinearColor CrosshairColorWhenCantFit = FLinearColor::Red;

	UPROPERTY(EditAnywhere)
	FVector2D CrosshairSize{50.0f, 50.0f};

	ANativeHud();

	virtual UInventoryWidget* GetInventoryWidget();

	virtual UMainPlayerUi* GetMainPlayerUi();

	virtual void CantFitPickUpEvent();

	void ShowHud();

	void HideHud();
protected:
	virtual void BeginPlay() override;

	void DrawHUD() override;
private:
	FTimerHandle CantFitTimerHandle;
	FLinearColor CurrentCrosshairColor = CrosshairColor;

	UPROPERTY()
	UInventoryWidget* InventoryWidget;

	UPROPERTY()
	UMainPlayerUi* MainPlayerUi;

	bool bDoShowCrosshair = true;
};
