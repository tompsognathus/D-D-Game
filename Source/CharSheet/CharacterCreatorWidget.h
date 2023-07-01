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
	int StrScore = 8;
	int DexScore = 8;
	int ConScore = 8;
	int IntScore = 8;
	int WisScore = 8;
	int ChaScore = 8;

	int RemainingPointBuy = 27;

	FString SelectedRace = "";
	FString SelectedClass = "";

	FString Name = "";

	FString PronounHe = "";
	FString PronounHim = "";
	FString PronounHis = "";


protected:
	// Doing setup in the C++ constructor is not as
	// useful as using NativeConstruct.
	virtual void NativeConstruct() override;

	// Ability Score Functions
	void DisplayAbilityScoresAndUpdateModifiers();

	void UpdateAbilityModifiers();

	int CalculateAbilityModifier(int AbilityScore);

	// Point Buy Functions
	void SetPointBuyText(int NewScore);

	int CalculateRemainingPointBuy();

	int CalculatePointValue(int AbilityScore);

	// UI Elements
	UFUNCTION()
	void OnSubmitBtnClicked();
	UFUNCTION()
	void OnRaceSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectType);
	UFUNCTION()
	void OnClassSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectType);
	UFUNCTION()
	void OnNameTextChanged(const FText& Text);
	UFUNCTION()
	void OnPronounHeChanged(const FText& Text);
	UFUNCTION()
	void OnPronounHimChanged(const FText& Text);
	UFUNCTION()
	void OnPronounHisChanged(const FText& Text);
	UFUNCTION()
	void IncreaseAbilityScore(int& AbilityScore, UButton* UpBtn, UButton* DownBtn);
	UFUNCTION()
	void DecreaseAbilityScore(int& AbilityScore, UButton* UpBtn, UButton* DownBtn);
	UFUNCTION()
	void UpdateAbilityBtnVisibility();
	UFUNCTION()
	void UpdateSingleAbilityBtnVisibility(int& AbilityScore, UButton* UpBtn, UButton* DownBtn);
	UFUNCTION()
	void UpdatePointBuy();

	UFUNCTION()
	void OnStrBtnUpClicked();
	UFUNCTION()
	void OnStrBtnDownClicked();
	UFUNCTION()
	void OnDexBtnUpClicked();
	UFUNCTION()
	void OnDexBtnDownClicked();
	UFUNCTION()
	void OnConBtnUpClicked();
	UFUNCTION()
	void OnConBtnDownClicked();
	UFUNCTION()
	void OnIntBtnUpClicked();
	UFUNCTION()
	void OnIntBtnDownClicked();
	UFUNCTION()
	void OnWisBtnUpClicked();
	UFUNCTION()
	void OnWisBtnDownClicked();
	UFUNCTION()
	void OnChaBtnUpClicked();
	UFUNCTION()
	void OnChaBtnDownClicked();

	// Point Buy
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PointBuyText;

	// Submit Button
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* SubmitBtn;

	// Race & Class Selectors
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UComboBoxString* RaceComboBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UComboBoxString* ClassComboBox;

	// Text fields for name etc
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UEditableText* NameEditableText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UEditableText* PronounHeEditableText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UEditableText* PronounHimEditableText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UEditableText* PronounHisEditableText;

	// Up/Down buttons for ability scores and text fields for ability scores and modifiers
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* StrBtnUp;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* StrBtnDown;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StrScoreText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StrModText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* DexBtnUp;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* DexBtnDown;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* DexScoreText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* DexModText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* ConBtnUp;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* ConBtnDown;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ConScoreText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ConModText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* IntBtnUp;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* IntBtnDown;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* IntScoreText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* IntModText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* WisBtnUp;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* WisBtnDown;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* WisScoreText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* WisModText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* ChaBtnUp;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* ChaBtnDown;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ChaScoreText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ChaModText;

};
