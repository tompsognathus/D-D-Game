// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARSHEET_API UInteractable : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractable();

	UPROPERTY(BlueprintAssignable)
	FClickedDelegate OnClicked;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void OnActorClicked(AActor* ClickedActor, FKey ButtonClicked);
};
