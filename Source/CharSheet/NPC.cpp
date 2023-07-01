// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "DlgSystem/DlgManager.h"


// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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