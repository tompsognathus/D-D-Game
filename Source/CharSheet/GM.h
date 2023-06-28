// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DlgSystem/DlgDialogueParticipant.h"
#include "DlgSystem/DlgContext.h"

#include "GM.generated.h"


UCLASS()
class CHARSHEET_API AGM : public AActor, public IDlgDialogueParticipant
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/****** Dialogue System Variables ******/

	// Name of this participant
	// Used for GetParticipantName
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	FName DialogueParticipantName = FName("GM");

	// UI name of this participant, what is displayed inside the UI
	// Used for GetParticipantDisplayName
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	FText DialogueParticipantDisplayName = NSLOCTEXT("Characters", "GM", "GM");

	// Used for GetParticipantIcon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	UTexture2D* DialogueParticipantIcon;

	// Context used to control the Dialogue follow
	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	UDlgContext* DialogueContext = nullptr;

	// Struct used to get/set the Dialogue Values
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	//FDialogueDataValues DialogueDataStruct;


	FName GetParticipantName_Implementation() const override { return DialogueParticipantName; }
};
