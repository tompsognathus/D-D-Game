// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPEncounterWidget.generated.h"

// We make the class abstract, as we don't want to create
// instances of this, instead we want to create instances
// of our UMG Blueprint subclass.
UCLASS(ABSTRACT)
class CHARSHEET_API URPEncounterWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// Doing setup in the C++ constructor is not as
	// useful as using NativeConstruct.
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* AdventureText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* OptionText1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* OptionText2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* OptionText3;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* OptionText4;

	UFUNCTION(BlueprintCallable, Category = "Text Fields")
	void SetAdventureText(FText NewAdventureText);

	UFUNCTION(BlueprintCallable, Category = "Text Fields")
	void SetOptionText(int OptionNumber, FText NewOptionText);
};
