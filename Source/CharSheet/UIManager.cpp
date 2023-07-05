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

	// First create a parent widget that only contains a widget switcher and is used to hold 
	// all other widgets and add it to viewport
	CreateParentUIWidget();

	// Get a reference to the widget switcher we just created inside the parent
	WidgetSwitcher = Cast<UWidgetSwitcher>(ParentUIWidgetInstance->GetWidgetFromName("WidgetSwitcher"));

	// Create all widgets and add them to the widget switcher
	SetUpUIWidgets();

	// Bind to events in widgets - things like button presses
	BindToWidgets();

	// Display the character creator widget
	DisplayWidget(CharacterCreatorWidgetInstance);
}

/*
 * Create a parent widget that only contains a widget switcher and is used to hold all other widgets 
 * and add it to viewport
 */
void UUIManager::CreateParentUIWidget()
{
	ParentUIWidgetInstance = CreateWidget(GetWorld(), ParentUIWidgetAssetRef);
	ParentUIWidgetInstance->AddToViewport();
}

/*
 * Create all UI widgets and add them to the widget switcher
 */
void UUIManager::SetUpUIWidgets()
{
	CreateUIWidgets();
	AddWidgetsToWidgetSwitcher();
}

/*
 * Create all the different UI widgets. Make sure to always also update the AddWidgetsToWidgetSwitcher 
 * function when you add a widget here!!!
 */
void UUIManager::CreateUIWidgets()
{
	CharacterCreatorWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CharacterCreatorWidgetAssetRef);
	RPEncounterWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), RPEncounterWidgetAssetRef);
	HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetAssetRef);
	CharSheetWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CharSheetWidgetAssetRef);
}

/*
 * Add all the created widgets to the widget switcher. If you add something here, 
 * make sure you also created it in CreateUIWidgets!!!
 */
void UUIManager::AddWidgetsToWidgetSwitcher()
{
	if (WidgetSwitcher)
	{
		AddWidgetToWidgetSwitcher(CharacterCreatorWidgetInstance);
		AddWidgetToWidgetSwitcher(RPEncounterWidgetInstance);
		AddWidgetToWidgetSwitcher(HUDWidgetInstance);
		AddWidgetToWidgetSwitcher(CharSheetWidgetInstance);

	}
	else { UE_LOG(LogTemp, Error, TEXT("WidgetSwitcher not found")); }
}

/*
 * Add a widget to the widget switcher.
 * 
 * INPUT: UUserWidget* WidgetInstanceToAdd: The widget to be added to the WidgetSwitcher
 */
void UUIManager::AddWidgetToWidgetSwitcher(UUserWidget* WidgetInstanceToAdd)
{
	if (WidgetInstanceToAdd)
	{
		WidgetSwitcher->AddChild(WidgetInstanceToAdd);
	}
	else { UE_LOG(LogTemp, Error, TEXT("%s not found"), *WidgetInstanceToAdd->GetName()); }
}

/*
 * 
 */
void UUIManager::BindToWidgets()
{
	// Char Sheet Button(s) across different HUD widgets
	if (HUDWidgetInstance)
	{
		// Cast to HUDWidget and bind to OnCharSheetBtnClickedDelegate
		UHUDWidget* HUDWidget = Cast<UHUDWidget>(HUDWidgetInstance);
		if (HUDWidget)
		{
			HUDWidget->OnCharSheetBtnClickedDelegate.AddDynamic(this, &UUIManager::HandleCharSheetBtnClicked);
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

/*
 * Handle the char sheet button being clicked. Either display the char sheet widget or
 * return to the previous widget if we're already displaying the char sheet widget.
 */
void UUIManager::HandleCharSheetBtnClicked()
{
	// If we're in anything other than the char sheet widget, display it
	if (WidgetSwitcher)
	{
		UUserWidget* ActiveWidget = Cast<UUserWidget>(WidgetSwitcher->GetActiveWidget());

		if (ActiveWidget != CharSheetWidgetInstance)
		{
			DisplayWidget(CharSheetWidgetInstance);
		}
		else
		{
			// If we're in the char sheet widget, display the previous widget
			DisplayWidget(PreviousWidget);
		}
	}
}

/*
 * Use the widget switcher to display a widget on screen
 * 
 * INPUT: UUserWidget* WidgetInstanceToDisplay: The widget to be displayed
 */
void UUIManager::DisplayWidget(UUserWidget* WidgetInstanceToDisplay)
{
	PreviousWidget = Cast<UUserWidget>(WidgetSwitcher->GetActiveWidget());

	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidget(WidgetInstanceToDisplay);
	}
	else { UE_LOG(LogTemp, Error, TEXT("WidgetSwitcher not found")); }
}

/*
 * Display the RP Encounter creator widget
 */
void UUIManager::DisplayRPEncounterUIWidget()
{
	DisplayWidget(RPEncounterWidgetInstance);
}

/*
 * Get a reference to the existing Character Creator Widget
 * 
 * RETURNS: UCharacterCreatorWidget*: The character creator widget
 */
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

/*
 * Update the main encounter text on the RP Encounter widget
 * 
 * INPUT: FText MainText: The text to be displayed
 */
void UUIManager::SetRPEncounterBodyText(FText BodyText)
{
	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);

	if (RPEncounterWidget)
	{
		RPEncounterWidget->SetBodyText(BodyText);
	} else { UE_LOG(LogTemp, Error, TEXT("RPEncounterWidget not found")); }
}

/*
 * Update the option text on the RP Encounter widget
 * 
 * INPUT: int OptionNumber: The option number to be updated
 * INPUT: FText NewOptionText: The text to be displayed
 */
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

/*
 * Select one of the available dialogue options and display the next portion of the dialogue
 * 
 * INPUT: int OptionNumber: Index of the selected option (1-4)
 */
void UUIManager::SelectDialogueOption(int OptionNumber)
{
	if (OptionNumber < 0 || OptionNumber > 3)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid option number, must be between 1 and 4"));
		return;
	}

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
			DisplayWidget(HUDWidgetInstance);
		}

	} else { UE_LOG(LogTemp, Error, TEXT("GM not found")); }
}



