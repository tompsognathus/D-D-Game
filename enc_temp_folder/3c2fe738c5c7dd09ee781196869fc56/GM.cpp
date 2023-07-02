// Fill out your copyright notice in the Description page of Project Settings.


#include "GM.h"
#include "UIManager.h"
#include "CharSheetCharacter.h"
#include "Engine/Blueprint.h"
#include "CharacterCreatorWidget.h"


// Sets default values
AGM::AGM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGM::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to UIManager

}

// Called every frame
void AGM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGM::StartIncitingIncidentDialogue()
{
	StartDialogue(Dialogues[0], { this });
	
	if (UIManager)
	{
		UIManager->DisplayRPEncounterUIWidget();
		
		UIManager->SetRPEncounterBodyText(GetDialogueBodyText());
		TArray<FText> Options = GetDialogueOptionsText();

		for (int i = 0; i < Options.Num(); i++)
		{
			UIManager->SetRPEncounterOptionText(i+1, Options[i]); // Options are currently indexed from 1
		}
	} else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
}



