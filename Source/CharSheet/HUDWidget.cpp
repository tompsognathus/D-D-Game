// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CharSheetBtn->OnClicked.AddDynamic(this, &UHUDWidget::OnCharSheetBtnClicked);
}

void UHUDWidget::DisplayGpText(FText NewGpText)
{
	GpText->SetText(NewGpText);
}

void UHUDWidget::DisplayHp(float NewHpPercent)
{
	HpBar->SetPercent(NewHpPercent);
}

void UHUDWidget::DisplayXp(float NewXpPercent)
{
	XpBar->SetPercent(NewXpPercent);
}

void UHUDWidget::OnCharSheetBtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("CharSheetBtnClicked"));
}