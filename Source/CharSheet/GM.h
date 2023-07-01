// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"

#include "GM.generated.h"


UCLASS()
class CHARSHEET_API AGM : public ANPC
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

	void StartIncitingIncidentDialogue();

private:
	class UUIManager* UIManager;
	class UCharacterCreatorWidget* CharacterCreatorWidget;

};
