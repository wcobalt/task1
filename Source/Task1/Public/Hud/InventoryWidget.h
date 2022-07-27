// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/NativePlayerCharacter.h"
#include "UObject/Object.h"
#include "InventoryWidget.generated.h"

class UItem;
/**
 *
 */
UCLASS()
class TASK1_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float RotationStep = 3.0f;

	UPROPERTY(EditAnywhere)
	float ZoomStep = 0.01f;

	UPROPERTY(EditAnywhere)
	float ZoomMax = 20.0f;

	UPROPERTY(EditAnywhere)
	float ZoomMin = 5.0f;

	UPROPERTY(EditAnywhere)
	float SizeToFitIn = 10.0f;

	virtual void ShowInventory();

	virtual void CloseInventory();

	virtual void StartRotatingItem();

	virtual void StopRotatingItem();

	virtual void RotateItemVertically(float Value);

	virtual void RotateItemHorizontally(float Value);

	virtual void Zoom(float Value);

protected:
	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GetPlayerInventory() const;

	UFUNCTION(BlueprintCallable)
	void SetInspectingMesh(UStaticMesh* Mesh);

	void CenterMesh();

	void SetDefaultZoomAndRotation();

	float GetAdditionalScale() const;
private:
	bool bIsRotating = false;

	ANativePlayerCharacter* GetCharacter() const;

	void RotateInspectingMesh(FVector Axis, float Value);
};
