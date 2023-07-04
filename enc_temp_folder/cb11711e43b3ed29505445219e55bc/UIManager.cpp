// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "Kismet/GameplayStatics.h"

#include "Adventurer.h"
#include "GM.h"

#include "Components/WidgetSwitcher.h"
#include "CharacterCreatorWidget.h"
#include "HUDWidget.h"
#include "RPEncounterWidget.h"
#include "CharSheetWidget.h"



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

	CreateParentUIWidget();
	// Get widget switcher from parent ui widget
	WidgetSwitcher = Cast<UWidgetSwitcher>(ParentUIWidgetInstance->GetWidgetFromName("WidgetSwitcher"));

	CreateAllWidgets();
	BindToWidgets();

	DisplayCharacterCreatorUIWidget();
}


// Called every frame
void UUIManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
	CharSheetWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CharSheetWidgetAssetRef);

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

		if (CharSheetWidgetInstance)
		{
			WidgetSwitcher->AddChild(CharSheetWidgetInstance);
		} else { UE_LOG(LogTemp, Error, TEXT("CharSheetWidgetInstance not found")); }

	} else { UE_LOG(LogTemp, Error, TEXT("WidgetSwitcher not found")); }

}

void UUIManager::BindToWidgets()
{
	if (HUDWidgetInstance)
	{
		// Cast to HUDWidget and bind to OnCharSheetBtnClickedDelegate
		UHUDWidget* HUDWidget = Cast<UHUDWidget>(HUDWidgetInstance);
		if (HUDWidget)
		{
			HUDWidget->OnCharSheetBtnClickedDelegate.AddDynamic(this, &UUIManager::DisplayCharSheetUIWidget);
		} else { UE_LOG(LogTemp, Error, TEXT("HUDWidget not found")); }
	} else { UE_LOG(LogTemp, Error, TEXT("HUDWidgetInstance not found")); }


	if (RPEncounterWidgetInstance)
	{
		// Get UHUDWidget component from RP encounter widget and bind to OnCharSheetBtnClickedDelegate
		URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);
		if (RPEncounterWidget)
		{
			UHUDWidget* HUDWidget = RPEncounterWidget->GetHUDWidget();

			if (HUDWidget)
			{
				HUDWidget->OnCharSheetBtnClickedDelegate.AddDynamic(this, &UUIManager::HandleCharSheetBtnClicked);

				UE_LOG(LogTemp, Display, TEXT("Bound to RPEncounterWidget"));

			} else { UE_LOG(LogTemp, Error, TEXT("HUDWidget not found")); }
		} else { UE_LOG(LogTemp, Error, TEXT("RPEncounterWidget not found")); }
	} else { UE_LOG(LogTemp, Error, TEXT("RPEncounterWidgetInstance not found")); }


	if (CharSheetWidgetInstance)
	{
		// Get UHUDWidget component from char sheet widget and bind to OnCharSheetBtnClickedDelegate
		UCharSheetWidget* CharSheetWidget = Cast<UCharSheetWidget>(CharSheetWidgetInstance);
		if (CharSheetWidget)
		{
			UHUDWidget* HUDWidget = CharSheetWidget->GetHUDWidget();

			if (HUDWidget)
			{
				HUDWidget->OnCharSheetBtnClickedDelegate.AddDynamic(this, &UUIManager::HandleCharSheetBtnClicked);

			} else { UE_LOG(LogTemp, Error, TEXT("HUDWidget not found")); }
		} else { UE_LOG(LogTemp, Error, TEXT("CharSheetWidget not found")); }
	} else { UE_LOG(LogTemp, Error, TEXT("CharSheetWidgetInstance not found")); }
}

void UUIManager::HandleCharSheetBtnClicked()
{
	// If we're in anything other than the char sheet widget, display it
	if (WidgetSwitcher)
	{
		UUserWidget* ActiveWidget = Cast<UUserWidget>(WidgetSwitcher->GetActiveWidget());

		if (ActiveWidget != CharSheetWidgetInstance)
		{
			WidgetSwitcher->SetActiveWidget(CharSheetWidgetInstance);
		}
	}

}


void UUIManager::DisplayCharacterCreatorUIWidget()
{
	UE_LOG(LogTemp, Display, TEXT("DisplayCharacterCreatorUIWidget"));

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
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidget(HUDWidgetInstance);
	} else { UE_LOG(LogTemp, Error, TEXT("HUDWidgetInstance not found")); }
}

void UUIManager::DisplayCharSheetUIWidget()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidget(CharSheetWidgetInstance);
	} else { UE_LOG(LogTemp, Error, TEXT("WidgetSwitcher not found")); }
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



