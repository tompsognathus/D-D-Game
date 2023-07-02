// Fill out your copyright notice in the Description page of Project Settings.


#include "RPEncounterWidget.h"
#include "Components/TextBlock.h"

void URPEncounterWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void URPEncounterWidget::SetAdventureText(FText NewAdventureText)
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