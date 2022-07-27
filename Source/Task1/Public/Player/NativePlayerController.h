// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativePlayerCharacter.h"
#include "Sound/SoundCue.h"
#include "Pickups/Pickup.h"
#include "NativePlayerController.generated.h"

class ANativeHud;

UCLASS()
class TASK1_API ANativePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> PickupsChannel = ECC_GameTraceChannel1;

	UPROPERTY(EditAnywhere)
	float PickupDistance = 200.0f;

	UPROPERTY(EditAnywhere)
	float MouseSensitivity = 0.7f;

	UPROPERTY(EditAnywhere)
	FGameplayTag PickUpAbilityTag;

	UPROPERTY(EditAnywhere)
	FGameplayTag ToggleInventoryAbilityTag;

	UPROPERTY(EditAnywhere)
	FGameplayTag OpenedInventoryEffectTag;

	ANativePlayerController();

	virtual void Tick(float DeltaTime) override;

	APickup* RetrievePickupInSight() const;
protected:
	static const FName MoveForwardInput;
	static const FName MoveSidewaysInput;
	static const FName LookAroundVerticallyInput;
	static const FName LookAroundHorizontallyInput;
	static const FName RotateModeInput;
	static const FName PickUpInput;
	static const FName ToggleInventoryInput;
	static const FName ZoomInput;

	virtual void BeginPlay() override;

	virtual void TryToPickUpObject();

	virtual void ToggleInventory();

	virtual void StartRotatingItem();

	virtual void StopRotatingItem();

	virtual void Zoom(float Value);

	virtual void MoveForward(float Value);

	virtual void MoveSideways(float Value);

	virtual void RotateCameraVertically(float Value);

	virtual void RotateCameraHorizontally(float Value);

	void SetupInputComponent() override;

	virtual bool IsInventoryOpened() const;
public:
	ANativePlayerCharacter* GetNativePlayerCharacter() const;

	ANativeHud* GetNativeHud() const;
};
