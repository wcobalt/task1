// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NativePlayerController.h"

#include "Hud/NativeHud.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/Pickup.h"

const FName ANativePlayerController::MoveForwardInput("MoveForward");
const FName ANativePlayerController::MoveSidewaysInput("MoveSideways");
const FName ANativePlayerController::
	LookAroundVerticallyInput("LookAroundVertically");
const FName ANativePlayerController::
	LookAroundHorizontallyInput("LookAroundHorizontally");
const FName ANativePlayerController::RotateModeInput("RotateMode");
const FName ANativePlayerController::PickUpInput("PickUp");
const FName ANativePlayerController::ToggleInventoryInput("OpenInventory");
const FName ANativePlayerController::ZoomInput("Zoom");

ANativePlayerController::ANativePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANativePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ANativePlayerController::TryToPickUpObject()
{
	// GAS
	if (auto PlayerCharacter = GetNativePlayerCharacter())
	{
		FGameplayTagContainer Container;
		Container.AddTag(PickUpAbilityTag);

		PlayerCharacter->GetAbilitySystemComponent()
			->TryActivateAbilitiesByTag(Container);
	}
}

void ANativePlayerController::ToggleInventory()
{
	// GAS
	if (auto PlayerCharacter = GetNativePlayerCharacter())
	{
		FGameplayTagContainer Container;
		Container.AddTag(ToggleInventoryAbilityTag);

		PlayerCharacter->GetAbilitySystemComponent()
			->TryActivateAbilitiesByTag(Container);
	}
}

void ANativePlayerController::StartRotatingItem()
{
	if (IsInventoryOpened())
	{
		if (auto Hud = GetNativeHud())
		{
			Hud->GetInventoryWidget()->StartRotatingItem();
		}
	}
}

void ANativePlayerController::StopRotatingItem()
{
	if (IsInventoryOpened())
	{
		if (auto Hud = GetNativeHud())
		{
			Hud->GetInventoryWidget()->StopRotatingItem();
		}
	}
}

void ANativePlayerController::Zoom(float Value)
{
	if (IsInventoryOpened())
	{
		if (auto Hud = GetNativeHud())
		{
			Hud->GetInventoryWidget()->Zoom(Value);
		}
	}
}

void ANativePlayerController::MoveForward(float Value)
{
	if (IsInventoryOpened()) return;

	if (auto PlayerCharacter = GetNativePlayerCharacter())
	{
		PlayerCharacter->MoveForward(Value);
	}
}

void ANativePlayerController::MoveSideways(float Value)
{
	if (IsInventoryOpened()) return;

	if (auto PlayerCharacter = GetNativePlayerCharacter())
	{
		PlayerCharacter->MoveSideways(Value);
	}
}

void ANativePlayerController::RotateCameraVertically(float Value)
{
	float NormalizedValue = Value * MouseSensitivity;

	if (IsInventoryOpened())
	{
		if (auto Hud = GetNativeHud())
		{
			Hud->GetInventoryWidget()->RotateItemVertically(NormalizedValue);
		}
	}
	else if (auto PlayerCharacter = GetNativePlayerCharacter())
	{
		PlayerCharacter->RotateCameraVertically(NormalizedValue);
	}
}

void ANativePlayerController::RotateCameraHorizontally(float Value)
{
	float NormalizedValue = Value * MouseSensitivity;

	if (IsInventoryOpened())
	{
		if (auto Hud = GetNativeHud())
		{
			Hud->GetInventoryWidget()->RotateItemHorizontally(NormalizedValue);
		}
	}
	else if (auto PlayerCharacter = GetNativePlayerCharacter())
	{
		PlayerCharacter->RotateCameraHorizontally(NormalizedValue);
	}
}

void ANativePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// axes
	InputComponent->BindAxis(LookAroundHorizontallyInput, this,
		&ANativePlayerController::RotateCameraHorizontally);
	InputComponent->BindAxis(LookAroundVerticallyInput, this,
		&ANativePlayerController::RotateCameraVertically);
	InputComponent->BindAxis(ZoomInput, this,
		&ANativePlayerController::Zoom);
	InputComponent->BindAxis(MoveForwardInput, this,
		&ANativePlayerController::MoveForward);
	InputComponent->BindAxis(MoveSidewaysInput, this,
		&ANativePlayerController::MoveSideways);

	// actions
	InputComponent->BindAction(ToggleInventoryInput, IE_Released,
		this, &ANativePlayerController::ToggleInventory);
	InputComponent->BindAction(PickUpInput, IE_Pressed, this,
		&ANativePlayerController::TryToPickUpObject);
	InputComponent->BindAction(RotateModeInput, IE_Pressed, this,
		&ANativePlayerController::StartRotatingItem);
	InputComponent->BindAction(RotateModeInput, IE_Released, this,
		&ANativePlayerController::StopRotatingItem);
}

bool ANativePlayerController::IsInventoryOpened() const
{
	if (auto PlayerCharacter = GetNativePlayerCharacter())
	{
		FGameplayTagContainer Container;
		Container.AddTag(OpenedInventoryEffectTag);

		bool bIsOpened = (PlayerCharacter->GetAbilitySystemComponent()
			->GetActiveEffectsWithAllTags(Container).Num() != 0);

		return bIsOpened;
	}

	return false;
}

ANativePlayerCharacter*
	ANativePlayerController::GetNativePlayerCharacter() const
{
	return Cast<ANativePlayerCharacter>(GetPawn());
}

ANativeHud* ANativePlayerController::GetNativeHud() const
{
	return Cast<ANativeHud>(GetHUD());
}

void ANativePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//@todo consider moving to a timer and mb to a component

	if (auto Hud = GetNativeHud())
	{
		Hud->GetMainPlayerUi()->SetPickupInSight(RetrievePickupInSight());
	}
}

APickup* ANativePlayerController::RetrievePickupInSight() const
{
	if (auto PlayerCharacter = GetNativePlayerCharacter())
	{
		FVector CameraCenter;
		FVector CameraForwardVector;
		PlayerCharacter->GetCameraRotation(CameraCenter,
			CameraForwardVector);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult,
			CameraCenter,
			CameraCenter + CameraForwardVector * PickupDistance,
			PickupsChannel);

		return Cast<APickup>(HitResult.GetActor());
	}

	return nullptr;
}

