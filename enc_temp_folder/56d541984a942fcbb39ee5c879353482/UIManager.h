// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARSHEET_API UUIManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUIManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Character Creator Widget Blueprint - Reference UMG Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> CharacterCreatorWidgetAssetRef;

	// RP Encounter Widget Blueprint - Reference UMG Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> RPEncounterWidgetAssetRef;

	// GM Blueprint - Reference GM Blueprint Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class ANPC> GMBlueprintRef;

	class AGM* GM;

	UFUNCTION()
	void DisplayCharacterCreatorUIWidget();

	UFUNCTION()
	UCharacterCreatorWidget* GetCharacterCreatorUIWidget();

	UFUNCTION()
	void DisplayRPEncounterUIWidget();



private:
	void CreateGmNpc();
	void CreateAllWidgets();
	void HideAllWidgets();
	void GetAdventurerReference();
	void CreateMyWidget(TSubclassOf<UUserWidget> WidgetRef, UUserWidget*& Widget);
	void DisplayWidget(UUserWidget*& Widget);

	// Adventurer class
	class UAdventurer* Adventurer;

	// Variable to hold the Character Creator Widget After Creating it
	UUserWidget* CharacterCreatorWidgetInstance;

	// Variable to hold the RP Encounter Widget After Creating it
	UUserWidget* RPEncounterWidgetInstance;

	// Variable to hold the GM After Creating it
	class ANPC* GMNPC;


};
