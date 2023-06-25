// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCreatorWidget.generated.h"

// We make the class abstract, as we don't want to create
// instances of this, instead we want to create instances
// of our UMG Blueprint subclass.
UCLASS(ABSTRACT)
class CHARSHEET_API UCharacterCreatorWidget : public UUserWidget
{
	GENERATED_BODY()
	

private:
	// Ability Score Values
	int StrScore = 0;
	int DexScore = 0;
	int ConScore = 0;
	int IntScore = 0;
	int WisScore = 0;
	int ChaScore = 0;

protected:
	// Doing setup in the C++ constructor is not as
	// useful as using NativeConstruct.
	virtual void NativeConstruct() override;

	void DisplayAbilityScoresAndUpdateModifiers(int StrScore, int DexScore, int ConScore, int IntScore, int WisScore, int ChaScore);

	void UpdateAbilityModifiers();

	int CalculateAbilityModifier(int AbilityScore);

	void SetPointBuyText(int NewScore);

	UFUNCTION()
	void OnSubmitBtnClicked();
	UFUNCTION()
	void OnRaceSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectType);
	UFUNCTION()
	void OnClassSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectType);

	// Ability scores
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StrVal;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* DexVal;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ConVal;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* IntVal;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* WisVal;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ChaVal;

	// Ability modifiers
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StrMod;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* DexMod;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ConMod;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* IntMod;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* WisMod;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ChaMod;

	// Point Buy
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PointBuyText;

	// Submit Button
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* SubmitBtn;

	// Race & Class Selectors
	class UComboBoxString* RaceComboBox;
	class UComboBoxString* ClassComboBox;

	// Text fields for name etc


};
