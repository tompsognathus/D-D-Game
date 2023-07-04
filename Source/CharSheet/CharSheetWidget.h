// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "HUDWidget.h"

#include "CharSheetWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHARSHEET_API UCharSheetWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Doing setup in the C++ constructor is not as
	// useful as using NativeConstruct.
	virtual void NativeConstruct() override;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UHUDWidget* HUDWidget;

public:
	UFUNCTION()
		UHUDWidget* GetHUDWidget();
	
};
