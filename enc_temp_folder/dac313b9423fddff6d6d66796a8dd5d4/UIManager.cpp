// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "Adventurer.h"
#include "CharacterCreatorWidget.h"
#include "GM.h"
#include "RPEncounterWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetSwitcher.h"



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
	CreateParentUIWidget();
	// Get widget switcher from parent ui widget
	WidgetSwitcher = Cast<UWidgetSwitcher>(ParentUIWidgetInstance->GetWidgetFromName("WidgetSwitcher"));

	CreateAllWidgets();

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

void UUIManager::CreateParentUIWidget()
{
	ParentUIWidgetInstance = CreateWidget(GetWorld(), ParentUIWidgetAssetRef);
	ParentUIWidgetInstance->AddToViewport();
}

void UUIManager::CreateAllWidgets()
{
	CharacterCreatorWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CharacterCreatorWidgetAssetRef);
	RPEncounterWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), RPEncounterWidgetAssetRef);
	HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetAssetRef);

	// Add created widgets to widget switcher
	if (WidgetSwitcher)
	{
		if (CharacterCreatorWidgetInstance)
		{
			WidgetSwitcher->AddChild(CharacterCreatorWidgetInstance);

		} else { UE_LOG(LogTemp, Error, TEXT("CharacterCreatorWidgetInstance not found")); }

		if (RPEncounterWidgetInstance)
		{
			WidgetSwitcher->AddChild(RPEncounterWidgetInstance);

		} else { UE_LOG(LogTemp, Error, TEXT("RPEncounterWidgetInstance not found")); }

		if (HUDWidgetInstance)
		{
			WidgetSwitcher->AddChild(HUDWidgetInstance);
		} else { UE_LOG(LogTemp, Error, TEXT("HUDWidgetInstance not found")); }

	} else { UE_LOG(LogTemp, Error, TEXT("WidgetSwitcher not found")); }

}

void UUIManager::DisplayCharacterCreatorUIWidget()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidget(CharacterCreatorWidgetInstance);
	} else { UE_LOG(LogTemp, Error, TEXT("WidgetSwitcher not found")); }
}

UCharacterCreatorWidget* UUIManager::GetCharacterCreatorUIWidget()
{
	// Get character creator widget from UUserWidget
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
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidget(RPEncounterWidgetInstance);
	} else { UE_LOG(LogTemp, Error, TEXT("WidgetSwitcher not found")); }
}

void UUIManager::SetRPEncounterBodyText(FText BodyText)
{
	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);

	if (RPEncounterWidget)
	{
		RPEncounterWidget->SetBodyText(BodyText);
	} else { UE_LOG(LogTemp, Error, TEXT("RPEncounterWidget not found")); }
}

void UUIManager::SetRPEncounterOptionText(int OptionNumber, FText NewOptionText)
{
	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);

	if (RPEncounterWidget)
	{
		switch (OptionNumber)
		{
		case 1:
			RPEncounterWidget->SetOptionText(1, NewOptionText);
			break;
		case 2:
			RPEncounterWidget->SetOptionText(2, NewOptionText);
			break;
		case 3:
			RPEncounterWidget->SetOptionText(3, NewOptionText);
			break;
		case 4:
			RPEncounterWidget->SetOptionText(4, NewOptionText);
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Invalid option number"));
			break;
		}
	} else { UE_LOG(LogTemp, Error, TEXT("RPEncounterWidget not found")); }
}

void UUIManager::DisplayHUDUIWidget()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->AddToViewport();
	} else { UE_LOG(LogTemp, Error, TEXT("HUDWidgetInstance not found")); }
}

void UUIManager::SelectDialogueOption(int OptionNumber)
{
	if (GM)
	{
		bool HasReachedEndOfDialogue = !(GM->SelectDialogueOption(OptionNumber));
		UE_LOG(LogTemp, Display, TEXT("HasReachedEndOfDialogue: %s"), HasReachedEndOfDialogue ? TEXT("true") : TEXT("false"));
		if (!HasReachedEndOfDialogue)
		{
			GM->PopulateDialogueBodyText();
			GM->PopulateDialogueOptionsText();
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Reached end of dialogue"));
			DisplayHUDUIWidget();
		}

	} else { UE_LOG(LogTemp, Error, TEXT("GM not found")); }
}



