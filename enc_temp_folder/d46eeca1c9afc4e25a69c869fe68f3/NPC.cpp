// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "DlgSystem/DlgManager.h"
#include "CharSheetCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UIManager.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Get UI Manager reference through posessed pawn
    ACharSheetCharacter* PlayerCharacter = Cast<ACharSheetCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (PlayerCharacter)
    {
        UIManager = PlayerCharacter->FindComponentByClass<UUIManager>();
    } else { UE_LOG(LogTemp, Error, TEXT("PlayerCharacter not found")); }
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ANPC::StartDialogue(UDlgDialogue* Dialogue, const TArray<UObject*>& DlgParticipants)
{
    DialogueContext = UDlgManager::StartDialogue(Dialogue, DlgParticipants);
    return DialogueContext != nullptr;
}

FText ANPC::GetDialogueBodyText()
{
    if (!DialogueContext)
    {
        UE_LOG(LogTemp, Error, TEXT("DialogueContext is null"));
	}

    const FText Text = DialogueContext->GetActiveNodeText();

    return Text;
}

TArray<FText> ANPC::GetDialogueOptionsText()
{
    if (!DialogueContext)
    {
		UE_LOG(LogTemp, Error, TEXT("DialogueContext is null"));
	}

	TArray<FText> Options;
    int OptionsNum = DialogueContext->GetOptionsNum();

    for (int i = 0; i < OptionsNum; i++)
    {
		Options.Add(DialogueContext->GetOptionText(i));
	}

	return Options;
}


bool ANPC::SelectDialogueOption(int32 Index)
{
    if (!DialogueContext || !DialogueContext->IsValidOptionIndex(Index))
    {
        return false;
    }

    if (!DialogueContext->ChooseOption(Index) || DialogueContext->HasDialogueEnded())
    {
        // Dialogue Has Ended
        DialogueContext = nullptr;
        return false;
    }

    return true;
}