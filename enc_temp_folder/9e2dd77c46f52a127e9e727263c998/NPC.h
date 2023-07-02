// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DlgSystem/DlgDialogueParticipant.h"
#include "DlgSystem/DlgContext.h"

#include "NPC.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CHARSHEET_API ANPC : public AActor, public IDlgDialogueParticipant
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/****** Dialogue System Variables ******/

	// Name of this participant, used for GetParticipantName
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	FName DialogueParticipantName;

	// UI name of this participant, what is displayed inside the UI
	// Used for GetParticipantDisplayName
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	FText DialogueParticipantDisplayName = NSLOCTEXT("ExampleNamespace", "ExampleCharacterName", "ExampleParticipantName");


	// Used for GetParticipantIcon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	UTexture2D* DialogueParticipantIcon;

	// Context used to control the Dialogue follow
	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	UDlgContext* DialogueContext = nullptr;

	// Function to start the dialogue
	UFUNCTION(BlueprintCallable, Category = Dialogue)
	bool StartDialogue(UDlgDialogue* Dialogue, const TArray<UObject*>& Participants);

	// Functionto advance through the dialogue
	UFUNCTION(BlueprintCallable, Category = Dialogue)
	bool SelectDialogueOption(int32 Index);

	// Character's dialogue assets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	TArray<UDlgDialogue*> Dialogues;

	// Character's dialogue participants
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	TArray<UObject*> Participants;


	FName GetParticipantName_Implementation() const override 
	{ 
		UE_LOG(LogTemp, Display, TEXT("Participant Name: %s"), *DialogueParticipantName.ToString());
		return DialogueParticipantName; 
	}

	FText GetParticipantDisplayName_Implementation(FName ActiveSpeaker) const override 
	{ 
		UE_LOG(LogTemp, Display, TEXT("Participant Display Name: %s"), *DialogueParticipantDisplayName.ToString());
		return DialogueParticipantDisplayName; 
	}
	
	UTexture2D* GetParticipantIcon_Implementation(FName ActiveSpeaker, FName ActiveSpeakerState) const override { return DialogueParticipantIcon; }

	
};
