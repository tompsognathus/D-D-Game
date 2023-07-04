// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharSheetBtnClickedSignature);

UCLASS()
class CHARSHEET_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// Doing setup in the C++ constructor is not as
	// useful as using NativeConstruct.
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* CharSheetBtn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* XpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* GpText;

private:
	UFUNCTION()
	void DisplayGpText(FText NewGpText);

	UFUNCTION()
	void DisplayHp(float NewHpPercent);

	UFUNCTION()
	void DisplayXp(float NewXpPercent);

	UFUNCTION()
	void HandleCharSheetBtnClick();

public:
	UPROPERTY(BlueprintAssignable, Category = "Button")
	FCharSheetBtnClickedSignature OnCharSheetBtnClickedDelegate;

};
