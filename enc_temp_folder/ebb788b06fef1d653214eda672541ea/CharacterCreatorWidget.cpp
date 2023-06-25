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

	StrBtnUp->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnStrBtnUpClicked);	
	StrBtnDown->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnStrBtnDownClicked);

	DexBtnUp->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnDexBtnUpClicked);
	DexBtnDown->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnDexBtnDownClicked);

	ConBtnUp->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnConBtnUpClicked);
	ConBtnDown->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnConBtnDownClicked);

	IntBtnUp->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnIntBtnUpClicked);
	IntBtnDown->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnIntBtnDownClicked);

	WisBtnUp->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnWisBtnUpClicked);
	WisBtnDown->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnWisBtnDownClicked);

	ChaBtnUp->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnChaBtnUpClicked);
	ChaBtnDown->OnClicked.AddDynamic(this, &UCharacterCreatorWidget::OnChaBtnDownClicked);

	// Set default values
	DisplayAbilityScoresAndUpdateModifiers();
	SetPointBuyText(27);

}

// Ability Scores & Modifiers
void UCharacterCreatorWidget::DisplayAbilityScoresAndUpdateModifiers()
{
	if (StrScoreText)
	{
		StrScoreText->SetText(FText::FromString(FString::FromInt(StrScore)));
	}
	if (DexScoreText)
	{
		DexScoreText->SetText(FText::FromString(FString::FromInt(DexScore)));
	}
	if (ConScoreText)
	{
		ConScoreText->SetText(FText::FromString(FString::FromInt(ConScore)));
	}
	if (IntScoreText)
	{
		IntScoreText->SetText(FText::FromString(FString::FromInt(IntScore)));
	}
	if (WisScoreText)
	{
		WisScoreText->SetText(FText::FromString(FString::FromInt(WisScore)));
	}
	if (ChaScoreText)
	{
		ChaScoreText->SetText(FText::FromString(FString::FromInt(ChaScore)));
	}

	UpdateAbilityModifiers();
}


void UCharacterCreatorWidget::UpdateAbilityModifiers()
{
	if (StrScoreText && StrModText)
	{
		int StrModifier = CalculateAbilityModifier(StrScore);
		StrModText->SetText(FText::FromString(FString::FromInt(StrModifier)));
	}
	if (DexScoreText && DexModText)
	{
		int DexModifier = CalculateAbilityModifier(DexScore);
		DexModText->SetText(FText::FromString(FString::FromInt(DexModifier)));
	}
	if (ConScoreText && ConModText)
	{
		int ConModifier = CalculateAbilityModifier(ConScore);
		ConModText->SetText(FText::FromString(FString::FromInt(ConModifier)));
	}
	if (IntScoreText && IntModText)
	{
		int IntModifier = CalculateAbilityModifier(IntScore);
		IntModText->SetText(FText::FromString(FString::FromInt(IntModifier)));
	}
	if (WisScoreText && WisModText)
	{
		int WisModifier = CalculateAbilityModifier(WisScore);
		WisModText->SetText(FText::FromString(FString::FromInt(WisModifier)));
	}
	if (ChaScoreText && ChaModText)
	{
		int ChaModifier = CalculateAbilityModifier(ChaScore);
		ChaModText->SetText(FText::FromString(FString::FromInt(ChaModifier)));
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



void UCharacterCreatorWidget::OnStrBtnUpClicked()
{
	StrScore++;
	DisplayAbilityScoresAndUpdateModifiers();

}

void UCharacterCreatorWidget::OnStrBtnDownClicked()
{
	StrScore--;
	DisplayAbilityScoresAndUpdateModifiers();
}

void UCharacterCreatorWidget::OnDexBtnUpClicked()
{

}

void UCharacterCreatorWidget::OnDexBtnDownClicked()
{

}

void UCharacterCreatorWidget::OnConBtnUpClicked()
{

}

void UCharacterCreatorWidget::OnConBtnDownClicked()
{

}

void UCharacterCreatorWidget::OnIntBtnUpClicked()
{

}

void UCharacterCreatorWidget::OnIntBtnDownClicked()
{

}

void UCharacterCreatorWidget::OnWisBtnUpClicked()
{

}

void UCharacterCreatorWidget::OnWisBtnDownClicked()
{

}

void UCharacterCreatorWidget::OnChaBtnUpClicked()
{

}

void UCharacterCreatorWidget::OnChaBtnDownClicked()
{

}

