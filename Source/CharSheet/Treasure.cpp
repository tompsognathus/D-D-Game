// Fill out your copyright notice in the Description page of Project Settings.


#include "Treasure.h"
#include "Components/ArrowComponent.h"
#include "Interactable.h"

// Sets default values
ATreasure::ATreasure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATreasure::RotateLid()
{
	// Rotate lid by rotating the arrow component using RotationSpeed
	FRotator CurrentRotation = Arrow->GetComponentRotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, FRotator(0.0f, TargetLidAngle, 0.0f), GetWorld()->DeltaTimeSeconds, LidRotationSpeed);
	Arrow->SetWorldRotation(NewRotation);

}

// Called when the game starts or when spawned
void ATreasure::BeginPlay()
{
	Super::BeginPlay();

	Arrow = FindComponentByClass<UArrowComponent>();
}

// Called every frame
void ATreasure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRotating)
	{
		RotateLid();

		// If we've reached the target angle, stop rotating
		if (FMath::IsNearlyEqual(Arrow->GetComponentRotation().Yaw, TargetLidAngle, 1.0f))
		{
			// Snap to target rotation
			FRotator NewRotation = FRotator(0.0f, TargetLidAngle, 0.0f);
			Arrow->SetWorldRotation(NewRotation);

			IsRotating = false;

			UE_LOG(LogTemp, Display, TEXT("Rotating to %f"), TargetLidAngle);
		}
	}
}

void ATreasure::OpenLid()
{
	IsRotating = true;
	TargetLidAngle = LidOpenAngle;
}

void ATreasure::CloseLid()
{
	IsRotating = true;
	TargetLidAngle = LidClosedAngle;
}

void ATreasure::HandleInteractableClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Treasure clicked"));

	// Get owner actor
	AActor* OwnerActor = GetOwner();

	if (OwnerActor)
	{
		// Set custom depth on root component to show toon outlines
		// Get all mesh components
		TArray<UStaticMeshComponent*> MeshComponents;
		OwnerActor->GetComponents<UStaticMeshComponent>(MeshComponents);

		// Set custom depth on all mesh components
		for (UStaticMeshComponent* MeshComponent : MeshComponents)
		{
			MeshComponent->SetRenderCustomDepth(true);
		}
	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find treasure owner actor")); }
}

