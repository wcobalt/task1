// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/CharacterAttributeSet.h"
#include "Abilities/NativeGameplayAbility.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Pickups/Pickup.h"
#include "NativePlayerCharacter.generated.h"

class ANativePlayerController;
class USoundCue;

UCLASS()
class TASK1_API ANativePlayerCharacter : public ACharacter,
	public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ANativePlayerCharacter();

	UPROPERTY(EditAnywhere)
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere)
	USceneComponent* InspectingMeshOrigin;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* InspectingMesh;

	UPROPERTY(EditAnywhere)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	UCharacterAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UNativeGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> AttributesInitializer;
protected:
	virtual void BeginPlay() override;

	virtual void InitializeAttributes();

	virtual void GiveDefaultAbilities();
public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(
		class UInputComponent* PlayerInputComponent) override;

	virtual void MoveForward(float Value);

	virtual void MoveSideways(float Value);

	virtual void RotateCameraVertically(float Value);

	virtual void RotateCameraHorizontally(float Value);

	virtual void GetCameraRotation(FVector& CameraCenter,
		FVector& CameraForwardVector);

	void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
