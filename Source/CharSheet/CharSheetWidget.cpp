// Fill out your copyright notice in the Description page of Project Settings.


#include "CharSheetWidget.h"

void UCharSheetWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

UHUDWidget* UCharSheetWidget::GetHUDWidget()
{
	return HUDWidget;
}
