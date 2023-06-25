// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCreatorWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"
#include "Adventurer.h"
#include "Kismet/GameplayStatics.h"



void UCharacterCreatorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind delegates
	SubmitBtn->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnSubmitBtnClicked);
	RaceComboBox->OnSelectionChanged.AddDynamic(this, &UCharacterCreatorWidget::OnRaceSelectionChanged);
	ClassComboBox->OnSelectionChanged.AddDynamic(this, &UCharacterCreatorWidget::OnClassSelectionChanged);
	NameEditableText->OnTextChanged.AddDynamic(this, &UCharacterCreatorWidget::OnNameTextChanged);
	PronounHeEditableText->OnTextChanged.AddDynamic(this, &UCharacterCreatorWidget::OnPronounHeChanged);
	PronounHimEditableText->OnTextChanged.AddDynamic(this, &UCharacterCreatorWidget::OnPronounHimChanged);
	PronounHisEditableText->OnTextChanged.AddDynamic(this, &UCharacterCreatorWidget::OnPronounHisChanged);

	// Set default values
	DisplayAbilityScoresAndUpdateModifiers(8, 8, 8, 8, 8, 8);
	SetPointBuyText(27);

}

// Ability Scores & Modifiers
void UCharacterCreatorWidget::DisplayAbilityScoresAndUpdateModifiers(int NewStrScore, int NewDexScore, int NewConScore, int NewIntScore, int NewWisScore, int NewChaScore)
{
	if (StrVal)
	{
		StrVal->SetText(FText::FromString(FString::FromInt(NewStrScore)));
		StrScore = NewStrScore;
	}
	if (DexVal)
	{
		DexVal->SetText(FText::FromString(FString::FromInt(NewDexScore)));
		DexScore = NewDexScore;
	}
	if (ConVal)
	{
		ConVal->SetText(FText::FromString(FString::FromInt(NewConScore)));
		ConScore = NewConScore;
	}
	if (IntVal)
	{
		IntVal->SetText(FText::FromString(FString::FromInt(NewIntScore)));
		IntScore = NewIntScore;
	}
	if (WisVal)
	{
		WisVal->SetText(FText::FromString(FString::FromInt(NewWisScore)));
		WisScore = NewWisScore;
	}
	if (ChaVal)
	{
		ChaVal->SetText(FText::FromString(FString::FromInt(NewChaScore)));
		ChaScore = NewChaScore;
	}

	UpdateAbilityModifiers();
}


void UCharacterCreatorWidget::UpdateAbilityModifiers()
{
	if (StrVal && StrMod)
	{
		int StrModifier = CalculateAbilityModifier(StrScore);
		StrMod->SetText(FText::FromString(FString::FromInt(StrModifier)));
	}
	if (DexVal && DexMod)
	{
		int DexModifier = CalculateAbilityModifier(DexScore);
		DexMod->SetText(FText::FromString(FString::FromInt(DexModifier)));
	}
	if (ConVal && ConMod)
	{
		int ConModifier = CalculateAbilityModifier(ConScore);
		ConMod->SetText(FText::FromString(FString::FromInt(ConModifier)));
	}
	if (IntVal && IntMod)
	{
		int IntModifier = CalculateAbilityModifier(IntScore);
		IntMod->SetText(FText::FromString(FString::FromInt(IntModifier)));
	}
	if (WisVal && WisMod)
	{
		int WisModifier = CalculateAbilityModifier(WisScore);
		WisMod->SetText(FText::FromString(FString::FromInt(WisModifier)));
	}
	if (ChaVal && ChaMod)
	{
		int ChaModifier = CalculateAbilityModifier(ChaScore);
		ChaMod->SetText(FText::FromString(FString::FromInt(ChaModifier)));
	}
}


int UCharacterCreatorWidget::CalculateAbilityModifier(int AbilityScore)
{
	// Calculate the modifier
	int Modifier = (AbilityScore - 10) / 2;

	return Modifier;
}


// Point Buy
void UCharacterCreatorWidget::SetPointBuyText(int NewScore)
{
	FText NewText = FText::FromString(FString::FromInt(NewScore));
	if (PointBuyText)
	{
		PointBuyText->SetText(NewText);
	}
}


// React to UI Interactions
void UCharacterCreatorWidget::OnSubmitBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Submit button clicked"));
	// Get reference to Adventurer component from player character
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APawn* PlayerPawn = PlayerController->GetPawn();
	UAdventurer* Adventurer = PlayerPawn->FindComponentByClass<UAdventurer>();

	// Set variables in Adventurer compoenent
	if (Adventurer)
	{
		// Ability scores
		Adventurer->SetAdventurerAbilityScores(StrScore, DexScore, ConScore, IntScore, WisScore, ChaScore);
		// Ability modifiers are updated automatically whenever an ability score is set
	
		// Race & Class
		Adventurer->SetAdventurerRace(SelectedRace);
		Adventurer->SetAdventurerClass(SelectedClass);

		// Name & Pronouns
		Adventurer->SetAdventurerName(Name);
		Adventurer->SetAdventurerPronouns(PronounHe, PronounHim, PronounHis);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Adventurer component not found"));
	}
}

void UCharacterCreatorWidget::OnRaceSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectType)
{
	UE_LOG(LogTemp, Display, TEXT("Race selection changed"));
	SelectedRace = SelectedItem;
}

void UCharacterCreatorWidget::OnClassSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectType)
{
	UE_LOG(LogTemp, Display, TEXT("Class selection changed"));
	SelectedClass = SelectedItem;
}

void UCharacterCreatorWidget::OnNameTextChanged(const FText& Text)
{
	UE_LOG(LogTemp, Display, TEXT("Name text changed"));
	Name = Text.ToString();
}

void UCharacterCreatorWidget::OnPronounHeChanged(const FText& Text)
{
	UE_LOG(LogTemp, Display, TEXT("Pronoun He text changed"));
	PronounHe = Text.ToString();
}

void UCharacterCreatorWidget::OnPronounHimChanged(const FText& Text)
{
	UE_LOG(LogTemp, Display, TEXT("Pronoun Him text changed"));
	PronounHim = Text.ToString();
}

void UCharacterCreatorWidget::OnPronounHisChanged(const FText& Text)
{
	UE_LOG(LogTemp, Display, TEXT("Pronoun His text changed"));
	PronounHis = Text.ToString();
}