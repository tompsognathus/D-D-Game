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


// Called every frame
void UInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractable::OnActorClicked(AActor* ClickedActor, FKey ButtonClicked)
{
	UE_LOG(LogTemp, Display, TEXT("Interactable clicked"));
}