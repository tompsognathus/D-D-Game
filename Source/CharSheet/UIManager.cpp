// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "Adventurer.h"
#include "CharacterCreatorWidget.h"
#include "GM.h"
#include "Kismet/GameplayStatics.h"


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

	CreateGmNpc();
	CreateAllWidgets();

	GetAdventurerReference();
	DisplayCharacterCreatorUIWidget();
}


// Called every frame
void UUIManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// Spawn GM from blueprint reference
void UUIManager::CreateGmNpc()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	GM = GetWorld()->SpawnActor<AGM>(GMBlueprintRef, SpawnParams);
	if (GM)
	{
		GM = Cast<AGM>(UGameplayStatics::GetActorOfClass(GetWorld(), AGM::StaticClass()));

	} else { UE_LOG(LogTemp, Error, TEXT("GM not spawned")); }
}

void UUIManager::CreateAllWidgets()
{
	CreateMyWidget(CharacterCreatorWidgetAssetRef, CharacterCreatorWidgetInstance);
	CreateMyWidget(RPEncounterWidgetAssetRef, RPEncounterWidgetInstance);
}

void UUIManager::HideAllWidgets()
{
	if (CharacterCreatorWidgetInstance)
	{
		CharacterCreatorWidgetInstance->RemoveFromParent();
	}
	if (RPEncounterWidgetInstance)
	{
		RPEncounterWidgetInstance->RemoveFromParent();
	}
	UE_LOG(LogTemp, Display, TEXT("Hiding all widgets"));
}

void UUIManager::DisplayCharacterCreatorUIWidget()
{
	HideAllWidgets();
	if (!CharacterCreatorWidgetInstance)
	{
		CreateMyWidget(CharacterCreatorWidgetAssetRef, CharacterCreatorWidgetInstance);
	}
	DisplayWidget(CharacterCreatorWidgetInstance);
}

UCharacterCreatorWidget* UUIManager::GetCharacterCreatorUIWidget()
{
	// get character creator widget from uuserwidget
	UCharacterCreatorWidget* FoundCharacterCreatorWidget = Cast<UCharacterCreatorWidget>(CharacterCreatorWidgetInstance);
	if (FoundCharacterCreatorWidget)
	{
		UE_LOG(LogTemp, Display, TEXT("Found Character Creator Widget"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't get Character Creator Widget!"));
	}
	return FoundCharacterCreatorWidget;
}

void UUIManager::DisplayRPEncounterUIWidget()
{
	HideAllWidgets();
	if (!RPEncounterWidgetInstance)
	{
		CreateMyWidget(RPEncounterWidgetAssetRef, RPEncounterWidgetInstance);
	}
	DisplayWidget(RPEncounterWidgetInstance);
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

