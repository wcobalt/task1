// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/InventoryWidget.h"

#include "Player/NativePlayerController.h"
#include "Player/NativePlayerState.h"

void UInventoryWidget::ShowInventory()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UInventoryWidget::CloseInventory()
{
	SetVisibility(ESlateVisibility::Collapsed);

	SetInspectingMesh(nullptr);
}

void UInventoryWidget::StartRotatingItem()
{
	UE_LOG(LogTemp, Error, TEXT("Start"));
	bIsRotating = true;
}

void UInventoryWidget::StopRotatingItem()
{
	UE_LOG(LogTemp, Error, TEXT("Stop"));
	bIsRotating = false;
}

void UInventoryWidget::RotateItemVertically(float Value)
{
	if (bIsRotating)
	{
		if (auto PlayerCharacter = GetCharacter())
		{
			FVector CameraRightAxis =
				PlayerCharacter->FirstPersonCamera->GetRightVector();

			RotateInspectingMesh(CameraRightAxis, Value);
		}
	}
}

void UInventoryWidget::RotateItemHorizontally(float Value)
{
	if (bIsRotating)
	{
		if (auto PlayerCharacter = GetCharacter())
		{
			FVector CameraUpAxis =
				PlayerCharacter->FirstPersonCamera->GetUpVector();

			RotateInspectingMesh(CameraUpAxis, Value);
		}
	}
}

void UInventoryWidget::Zoom(float Value)
{
	if (auto PlayerCharacter = GetCharacter())
	{
		UStaticMesh* Mesh = PlayerCharacter->InspectingMesh->GetStaticMesh();

		if (Mesh)
		{
			FVector Scale =
				PlayerCharacter->InspectingMesh->GetRelativeScale3D();
			FVector NewScale = Scale +
				 Scale * Value *
					FVector{ZoomStep, ZoomStep, ZoomStep};

			FBoxSphereBounds Bounds = Mesh->GetBounds();

			if (Bounds.SphereRadius * NewScale.X >= ZoomMin &&
				Bounds.SphereRadius * NewScale.X <= ZoomMax)
			{
				PlayerCharacter->InspectingMesh->SetRelativeScale3D(NewScale);
				CenterMesh();
			}
		}
	}
}

TArray<UItem*> UInventoryWidget::GetPlayerInventory() const
{
	if (auto PlayerState = GetWorld()->GetFirstPlayerController()
		->GetPlayerState<ANativePlayerState>())
	{
		return PlayerState->GetInventory();
	}

	return {};
}

void UInventoryWidget::SetInspectingMesh(UStaticMesh* Mesh)
{
	if (auto PlayerCharacter = GetCharacter())
	{
		PlayerCharacter->InspectingMesh->SetStaticMesh(Mesh);
		SetDefaultZoomAndRotation();
		CenterMesh();
	}
}

void UInventoryWidget::CenterMesh()
{
	if (auto PlayerCharacter = GetCharacter())
	{
		UStaticMesh* Mesh = PlayerCharacter->InspectingMesh->GetStaticMesh();
		FVector Scale = PlayerCharacter->InspectingMesh->GetRelativeScale3D();

		if (Mesh)
		{
			FBoxSphereBounds Bounds = Mesh->GetBounds();
			FVector Offset = -Bounds.Origin;
			Offset.X *= Scale.X;
			Offset.Y *= Scale.Y;
			Offset.Z *= Scale.Z;

			PlayerCharacter->InspectingMesh
				->SetRelativeLocation(Offset);
		}
		PlayerCharacter->InspectingMesh->SetStaticMesh(Mesh);
	}
}

void UInventoryWidget::SetDefaultZoomAndRotation()
{
	if (auto PlayerCharacter = GetCharacter())
	{
		UStaticMesh* Mesh = PlayerCharacter->InspectingMesh->GetStaticMesh();
		FVector Scale = PlayerCharacter->InspectingMesh->GetRelativeScale3D();

		if (Mesh)
		{
			PlayerCharacter->InspectingMesh->SetRelativeScale3D(
				Scale * GetAdditionalScale());
			PlayerCharacter->InspectingMeshOrigin->SetRelativeRotation(
				{0, 0, 0});
		}
	}
}

float UInventoryWidget::GetAdditionalScale() const
{
	if (auto PlayerCharacter = GetCharacter())
	{
		UStaticMesh* Mesh = PlayerCharacter->InspectingMesh->GetStaticMesh();
		FVector Scale = PlayerCharacter->InspectingMesh->GetRelativeScale3D();

		if (Mesh)
		{
			FBoxSphereBounds Bounds = Mesh->GetBounds();
			float ActualRadius = Scale.X * Bounds.SphereRadius;
			return SizeToFitIn / ActualRadius;
		}
	}

	return 0.0f;
}

ANativePlayerCharacter* UInventoryWidget::GetCharacter() const
{
	return Cast<ANativePlayerController>(GetWorld()
		->GetFirstPlayerController())->GetNativePlayerCharacter();
}

void UInventoryWidget::RotateInspectingMesh(FVector Axis, float Value)
{
	if (auto PlayerCharacter = GetCharacter())
	{
		UStaticMesh* Mesh =
			PlayerCharacter->InspectingMesh->GetStaticMesh();

		if (Mesh)
		{
			FRotator DeltaRotation{FQuat{Axis,
				RotationStep * -Value}};

			PlayerCharacter->InspectingMeshOrigin
				->AddWorldRotation(DeltaRotation);
		}
	}
}
