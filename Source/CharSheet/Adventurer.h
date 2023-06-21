// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Adventurer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARSHEET_API UAdventurer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAdventurer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Adventurer")
	void SetAdventurerName(FString NewName);

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
	void SetAdventurerPronounHe(FString NewName);

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
	void SetAdventurerPronounHim(FString NewName);

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
	void SetAdventurerPronounHis(FString NewName);

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
	void SetAdventurerRace(FString NewRace);

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
	void SetAdventurerClass(FString NewClass);

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
	void SetAdventurerAbilityScores(int Str, int Dex, int Con, int Int, int Wis, int Cha);

	UPROPERTY(BlueprintReadOnly)
	int PointsRemaining = 27;

private:
	int CalculateAbilityModifier(int AbilityScore);

	void UpdateModifiers();

	UPROPERTY(EditAnywhere)
	FString Name = "";

	UPROPERTY(EditAnywhere)
	FString PronounHe = "";

	UPROPERTY(EditAnywhere)
	FString PronounHim = "";

	UPROPERTY(EditAnywhere)
	FString PronounHis = "";

	UPROPERTY(EditAnywhere)
	FString CharRace = "";

	UPROPERTY(EditAnywhere)
	FString CharClass = "";


	UPROPERTY(EditAnywhere)
	int Level = 1;

	UPROPERTY(EditAnywhere)
	int Xp = 0;

public:
	// Ability Scores
	UPROPERTY(EditAnywhere)
	int Str = 8;
	UPROPERTY(EditAnywhere)
	int Dex = 8;
	UPROPERTY(EditAnywhere)
	int Con = 8;
	UPROPERTY(EditAnywhere)
	int Int = 8;
	UPROPERTY(EditAnywhere)
	int Wis = 8;
	UPROPERTY(EditAnywhere)
	int Cha = 8;

	// Ability Modifiers
	UPROPERTY(EditAnywhere)
	int StrMod = -1;
	UPROPERTY(EditAnywhere)
	int DexMod = -1;
	UPROPERTY(EditAnywhere)
	int ConMod = -1;
	UPROPERTY(EditAnywhere)
	int IntMod = -1;
	UPROPERTY(EditAnywhere)
	int WisMod = -1;
	UPROPERTY(EditAnywhere)
	int ChaMod = -1;


};
