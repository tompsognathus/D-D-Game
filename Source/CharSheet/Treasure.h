// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "Treasure.generated.h"

UCLASS()
class CHARSHEET_API ATreasure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreasure();

	void RotateLid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float LidRotationSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float LidOpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	float LidClosedAngle = 0.0f;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* Arrow;

	void OpenLid();
	void CloseLid();

	// Interactable interface
	void HandleInteractableClicked();


private:
	bool IsRotating = false;
	float TargetLidAngle = LidOpenAngle;
};
