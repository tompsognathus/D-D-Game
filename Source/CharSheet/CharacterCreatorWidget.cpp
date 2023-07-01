// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCreatorWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"
#include "Adventurer.h"
#include "UIManager.h"
#include "Kismet/GameplayStatics.h"
#include "GM.h"



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

int UCharacterCreatorWidget::CalculateRemainingPointBuy()
{
	RemainingPointBuy = 27;
	RemainingPointBuy -= CalculatePointValue(StrScore);
	RemainingPointBuy -= CalculatePointValue(DexScore);
	RemainingPointBuy -= CalculatePointValue(ConScore);
	RemainingPointBuy -= CalculatePointValue(IntScore);
	RemainingPointBuy -= CalculatePointValue(WisScore);
	RemainingPointBuy -= CalculatePointValue(ChaScore);

	return RemainingPointBuy;
}

int UCharacterCreatorWidget::CalculatePointValue(int AbilityScore)
{
	int PointValue = 0;

	// start at 9 since 8 is the lowest score and doesn't cost anything
	for (int i = 9; i <= AbilityScore; i++)
	{
		if (i <= 13)
		{
			PointValue += 1;
		}
		else
		{
			PointValue += 2;
		}
	}
	return PointValue;
}

// React to UI Interactions
void UCharacterCreatorWidget::OnSubmitBtnClicked()
{
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
	else { UE_LOG(LogTemp, Error, TEXT("Adventurer component not found")); }


	UUIManager* UIManager = PlayerPawn->FindComponentByClass<UUIManager>();
	if (UIManager)
	{
		AGM* GM = UIManager->GM;
		if (GM)
		{
			GM->StartIncitingIncidentDialogue();
			UIManager->DisplayRPEncounterUIWidget();
		}

		else { UE_LOG(LogTemp, Error, TEXT("GM not found")); }
	} 	else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
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

void UCharacterCreatorWidget::IncreaseAbilityScore(int& AbilityScore, UButton* UpBtn, UButton* DownBtn)
{
	if (AbilityScore < 15)
	{
		AbilityScore++;
		DisplayAbilityScoresAndUpdateModifiers();
	}
	UpdatePointBuy();
	UpdateAbilityBtnVisibility();
}

void UCharacterCreatorWidget::DecreaseAbilityScore(int& AbilityScore, UButton* UpBtn, UButton* DownBtn)
{
	if (AbilityScore > 8)
	{
		AbilityScore--;
		DisplayAbilityScoresAndUpdateModifiers();
	}
	UpdatePointBuy();
	UpdateAbilityBtnVisibility();
}

void UCharacterCreatorWidget::UpdateAbilityBtnVisibility()
{
	UpdateSingleAbilityBtnVisibility(StrScore, StrBtnUp, StrBtnDown);
	UpdateSingleAbilityBtnVisibility(DexScore, DexBtnUp, DexBtnDown);
	UpdateSingleAbilityBtnVisibility(ConScore, ConBtnUp, ConBtnDown);
	UpdateSingleAbilityBtnVisibility(IntScore, IntBtnUp, IntBtnDown);
	UpdateSingleAbilityBtnVisibility(WisScore, WisBtnUp, WisBtnDown);
	UpdateSingleAbilityBtnVisibility(ChaScore, ChaBtnUp, ChaBtnDown);
}


void UCharacterCreatorWidget::UpdateSingleAbilityBtnVisibility(int& AbilityScore, UButton* UpBtn, UButton* DownBtn)
{
	// Enable both buttons
	UpBtn->SetIsEnabled(true);
	DownBtn->SetIsEnabled(true);

	// Disable Up button if no points remaining
	if (RemainingPointBuy == 0)
	{
		UpBtn->SetIsEnabled(false);
	}
	// Disable Up button if score is 15 or higher
	else if (AbilityScore == 15)
	{
		UpBtn->SetIsEnabled(false);
	}
	// Disable Up button if score is 13+ and only 1 point remaining (need 2)
	else if (AbilityScore >= 13 && RemainingPointBuy < 2)
	{
		UpBtn->SetIsEnabled(false);
	}
	// Disable Down button if score is 8 or lower
	if (AbilityScore == 8)
	{
		DownBtn->SetIsEnabled(false);
	}
}

void UCharacterCreatorWidget::UpdatePointBuy()
{
	RemainingPointBuy = CalculateRemainingPointBuy();
	SetPointBuyText(RemainingPointBuy);
}

void UCharacterCreatorWidget::OnStrBtnUpClicked()
{
	IncreaseAbilityScore(StrScore, StrBtnUp, StrBtnDown);

}

void UCharacterCreatorWidget::OnStrBtnDownClicked()
{
	DecreaseAbilityScore(StrScore, StrBtnUp, StrBtnDown);
}

void UCharacterCreatorWidget::OnDexBtnUpClicked()
{
	IncreaseAbilityScore(DexScore, DexBtnUp, DexBtnDown);
}

void UCharacterCreatorWidget::OnDexBtnDownClicked()
{
	DecreaseAbilityScore(DexScore, DexBtnUp, DexBtnDown);
}

void UCharacterCreatorWidget::OnConBtnUpClicked()
{
	IncreaseAbilityScore(ConScore, ConBtnUp, ConBtnDown);
}

void UCharacterCreatorWidget::OnConBtnDownClicked()
{
	DecreaseAbilityScore(ConScore, ConBtnUp, ConBtnDown);
}

void UCharacterCreatorWidget::OnIntBtnUpClicked()
{
	IncreaseAbilityScore(IntScore, IntBtnUp, IntBtnDown);
}

void UCharacterCreatorWidget::OnIntBtnDownClicked()
{
	DecreaseAbilityScore(IntScore, IntBtnUp, IntBtnDown);

}

void UCharacterCreatorWidget::OnWisBtnUpClicked()
{
	IncreaseAbilityScore(WisScore, WisBtnUp, WisBtnDown);
}

void UCharacterCreatorWidget::OnWisBtnDownClicked()
{
	DecreaseAbilityScore(WisScore, WisBtnUp, WisBtnDown);
}

void UCharacterCreatorWidget::OnChaBtnUpClicked()
{
	IncreaseAbilityScore(ChaScore, ChaBtnUp, ChaBtnDown);
}

void UCharacterCreatorWidget::OnChaBtnDownClicked()
{
	DecreaseAbilityScore(ChaScore, ChaBtnUp, ChaBtnDown);
}

