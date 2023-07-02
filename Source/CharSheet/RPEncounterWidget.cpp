// Fill out your copyright notice in the Description page of Project Settings.


#include "RPEncounterWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void URPEncounterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind delegates

	//ensure(OptionBtn1 != nullptr);
	//OptionBtn1->OnClicked.AddDynamic(this, &URPEncounterWidget::OnOptionBtn1Clicked);

	//OptionBtn2->OnClicked.AddDynamic(this, &URPEncounterWidget::OnOptionBtn2Clicked);
	//OptionBtn3->OnClicked.AddDynamic(this, &URPEncounterWidget::OnOptionBtn3Clicked);
	//OptionBtn4->OnClicked.AddDynamic(this, &URPEncounterWidget::OnOptionBtn4Clicked);

}

void URPEncounterWidget::SetBodyText(FText NewAdventureText)
{
	if (AdventureText)
	{
		AdventureText->SetText(NewAdventureText);
	}
}

void URPEncounterWidget::SetOptionText(int OptionNumber, FText NewOptionText)
{
	switch (OptionNumber)
	{
	case 1:
		if (OptionText1)
		{
			OptionText1->SetText(NewOptionText);
		}
		break;
	case 2:
		if (OptionText2)
		{
			OptionText2->SetText(NewOptionText);
		}
		break;
	case 3:
		if (OptionText3)
		{
			OptionText3->SetText(NewOptionText);
		}
		break;
	case 4:
		if (OptionText4)
		{
			OptionText4->SetText(NewOptionText);
		}
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Invalid Option Number"))
			break;
	}
}

void URPEncounterWidget::OnOptionBtn1Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 1 Clicked"));
}

void URPEncounterWidget::OnOptionBtn2Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 2 Clicked"));
}

void URPEncounterWidget::OnOptionBtn3Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 3 Clicked"));
}

void URPEncounterWidget::OnOptionBtn4Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 4 Clicked"));
}