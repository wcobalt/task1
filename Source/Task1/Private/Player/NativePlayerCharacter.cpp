// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NativePlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/AudioComponent.h"
#include "Pickups/Pickup.h"
#include "Player/NativePlayerController.h"

ANativePlayerCharacter::ANativePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	FirstPersonCamera->SetupAttachment(RootComponent);

	InspectingMeshOrigin =
		CreateDefaultSubobject<USceneComponent>("Inspecting Mesh Origin");
	InspectingMeshOrigin->SetupAttachment(FirstPersonCamera);

	InspectingMesh =
		CreateDefaultSubobject<UStaticMeshComponent>("Inspecting Mesh");
	InspectingMesh->SetupAttachment(InspectingMeshOrigin);

	AbilitySystemComponent =
		CreateDefaultSubobject<UAbilitySystemComponent>("Ability System");

	AttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>("Attributes");
}

void ANativePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this,
		this);

	InitializeAttributes();
	GiveDefaultAbilities();
}

void ANativePlayerCharacter::InitializeAttributes()
{
	if (AttributesInitializer)
	{
		FGameplayEffectContextHandle EffectContext =
			AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle =
			AbilitySystemComponent->MakeOutgoingSpec(AttributesInitializer,
				1, EffectContext);

		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(
				*SpecHandle.Data.Get());
		}
	}
}

void ANativePlayerCharacter::GiveDefaultAbilities()
{
	for (auto& Ability : DefaultAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability,
			1, INDEX_NONE, this));
	}
}

void ANativePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANativePlayerCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANativePlayerCharacter::MoveForward(float Value)
{
	FVector Direction =
		FRotator{0, GetControlRotation().Yaw, 0}.Vector();

	AddMovementInput(Direction, Value);
}

void ANativePlayerCharacter::MoveSideways(float Value)
{
	FVector Direction =
		FRotator{0, GetControlRotation().Yaw, 0}.Vector();
	Direction = Direction.RotateAngleAxis(90, FVector::UpVector);

	AddMovementInput(Direction, Value);
}

void ANativePlayerCharacter::RotateCameraVertically(float Value)
{
	AddControllerPitchInput(Value);
}

void ANativePlayerCharacter::RotateCameraHorizontally(float Value)
{
	AddControllerYawInput(Value);
}

void ANativePlayerCharacter::GetCameraRotation(FVector& CameraCenter,
	FVector& CameraForwardVector)
{
	CameraCenter = FirstPersonCamera->GetComponentLocation();
	CameraForwardVector = GetControlRotation().Vector();
}

void ANativePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

UAbilitySystemComponent* ANativePlayerCharacter::
	GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

