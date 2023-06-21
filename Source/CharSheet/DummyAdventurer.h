// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DummyAdventurer.generated.h"

UCLASS()
class CHARSHEET_API ADummyAdventurer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummyAdventurer();

	// Clothing System
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clothing System")
	class USkeletalMeshComponent* AdventurerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* AdventurerWeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneCaptureComponent2D* RenderTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
