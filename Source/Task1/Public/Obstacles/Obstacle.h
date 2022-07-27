// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class TASK1_API AObstacle : public AActor
{
	GENERATED_BODY()

public:
	AObstacle();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ObstacleMesh;
protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
