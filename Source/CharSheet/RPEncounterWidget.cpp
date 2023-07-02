// Fill out your copyright notice in the Description page of Project Settings.


#include "RPEncounterWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "CharSheetCharacter.h"
#include "UIManager.h"
#include "Kismet/GameplayStatics.h"

void URPEncounterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OptionBtn1->OnClicked.AddDynamic(this, &URPEncounterWidget::OnOptionBtn1Clicked);
	OptionBtn2->OnClicked.AddDynamic(this, &URPEncounterWidget::OnOptionBtn2Clicked);
	OptionBtn3->OnClicked.AddDynamic(this, &URPEncounterWidget::OnOptionBtn3Clicked);
	OptionBtn4->OnClicked.AddDynamic(this, &URPEncounterWidget::OnOptionBtn4Clicked);

	// Get UI Manager reference through posessed pawn
	ACharSheetCharacter* PlayerCharacter = Cast<ACharSheetCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerCharacter)
	{
		UIManager = PlayerCharacter->FindComponentByClass<UUIManager>();
	}
	else { UE_LOG(LogTemp, Error, TEXT("PlayerCharacter not found")); }

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
	if (UIManager)
	{
		UIManager->SelectDialogueOption(0);
	} else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
}

void URPEncounterWidget::OnOptionBtn2Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 2 Clicked"));
	if (UIManager)
	{
		UIManager->SelectDialogueOption(1);
	}
	else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
}

void URPEncounterWidget::OnOptionBtn3Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 3 Clicked"));
	if (UIManager)
	{
		UIManager->SelectDialogueOption(2);
	}
	else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
}

void URPEncounterWidget::OnOptionBtn4Clicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 4 Clicked"));
	if (UIManager)
	{
		UIManager->SelectDialogueOption(3);
	}
	else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
}