// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Sets default values for this component's properties
UInteractable::UInteractable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Bind to parent actor's OnClick

}


// Called when the game starts
void UInteractable::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		// Subscribe to the actor's event
		Owner->OnClicked.AddDynamic(this, &UInteractable::OnActorClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner actor not found!"));
	}
}


void UInteractable::OnActorClicked(AActor* ClickedActor, FKey ButtonClicked)
{
	IsSelected = !IsSelected;

	if (IsSelected) { InteractableSelected(); }
	else { InteractableDeselected(); }
}

void UInteractable::InteractableSelected()
{
	UE_LOG(LogTemp, Display, TEXT("Interactable selected"));

	SetOutlineVisibility(true);

}

void UInteractable::InteractableDeselected()
{
	UE_LOG(LogTemp, Display, TEXT("Interactable deselected"));

	SetOutlineVisibility(false);
}

/*
 * Sets custom depth on all mesh components to show toon outlines
 * 
 * INPUT: bool OutlineIsVisible: whether or not to show the outline
 */
void UInteractable::SetOutlineVisibility(bool OutlineIsVisible)
{
	if (IsHighlightedOnClick)
	{
		AActor* Owner = GetOwner();
		if (Owner)
		{
			// Get all mesh components
			TArray<UStaticMeshComponent*> MeshComponents;
			Owner->GetComponents<UStaticMeshComponent>(MeshComponents);

			// Set custom depth on all mesh components
			for (UStaticMeshComponent* MeshComponent : MeshComponents)
			{
				MeshComponent->SetRenderCustomDepth(OutlineIsVisible);
			}
		}
		else { UE_LOG(LogTemp, Warning, TEXT("Owner actor not found!")); }
	}
}

