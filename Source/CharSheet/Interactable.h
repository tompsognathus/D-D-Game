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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	bool IsHighlightedOnClick = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable")
	bool IsSelected = false;

private:

	UFUNCTION()
	void OnActorClicked(AActor* ClickedActor, FKey ButtonClicked);

	UFUNCTION()
	void InteractableSelected();

	UFUNCTION()
	void InteractableDeselected();
	
	UFUNCTION()
	void SetOutlineVisibility(bool OutlineIsVisible);

};