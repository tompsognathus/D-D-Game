// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "Adventurer.h"
#include "CharacterCreatorWidget.h"


// Sets default values for this component's properties
UUIManager::UUIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UUIManager::BeginPlay()
{
	Super::BeginPlay();

	GetAdventurerReference();
	DisplayCharacterCreatorUI();

}


// Called every frame
void UUIManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UUIManager::HideAllWidgets()
{
	if (CharacterCreatorWidget)
	{
		CharacterCreatorWidget->RemoveFromParent();
	}
}

void UUIManager::DisplayCharacterCreatorUI()
{
	if (!CharacterCreatorWidget)
	{
		CreateMyWidget(CharacterCreatorWidgetRef, CharacterCreatorWidget);
	}
	DisplayWidget(CharacterCreatorWidget);
}

void UUIManager::DisplayRPEncounterUI()
{
	if (!RPEncounterWidget)
	{
		CreateMyWidget(RPEncounterWidgetRef, RPEncounterWidget);
	}
	DisplayWidget(RPEncounterWidget);
}


void UUIManager::CreateMyWidget(TSubclassOf<class UUserWidget> WidgetRef, UUserWidget*& Widget)
{
	if (WidgetRef) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetRef);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterCreatorWidgetRef on UIManager not set in blueprint"));
	}
}

void UUIManager::DisplayWidget(UUserWidget*& Widget)
{
	HideAllWidgets();
	if (Widget)
	{
		Widget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot add CharacterCreatorWidget to Viewport"));
	}
}

void UUIManager::GetAdventurerReference()
{
	if (GetOuter() && GetOuter()->IsA<AActor>())
	{
		AActor* OwnerActor = Cast<AActor>(GetOuter());
		Adventurer = OwnerActor->FindComponentByClass<UAdventurer>();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't get Adventurer reference"));
	}
}

