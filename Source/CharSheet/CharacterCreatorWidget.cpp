// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCreatorWidget.h"
#include "Components/TextBlock.h"

void UCharacterCreatorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Display, TEXT("Ping"));
	// Bind delegates and set up default appearance
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