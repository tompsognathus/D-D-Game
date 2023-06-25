// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Adventurer.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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
	void SetAdventurerPronouns(FString NewHe, FString NewHim, FString NewHis);

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
	void SetAdventurerRace(FString NewRace);

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
	void SetAdventurerClass(FString NewClass);

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
	void SetAdventurerAbilityScores(int Str, int Dex, int Con, int Int, int Wis, int Cha);


	UPROPERTY(BlueprintReadOnly)
	int PointsRemaining = 27;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Adventurer Settings")
	FString Name = "Bilbo Baggins";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Adventurer Settings")
	FString PronounHe = "he";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Adventurer Settings")
	FString PronounHim = "him";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Adventurer Settings")
	FString PronounHis = "his";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Adventurer Settings")
	FString CharRace = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Adventurer Settings")
	FString CharClass = "";


	UPROPERTY(BlueprintReadOnly)
	int Level = 1;

	UPROPERTY(BlueprintReadOnly)
	int Xp = 0;

	UPROPERTY(BlueprintReadOnly)
	int Gold = 25;

private:
	// Ability Scores
	UPROPERTY(VisibleAnywhere)
		int Str = 8;
	UPROPERTY(VisibleAnywhere)
		int Dex = 8;
	UPROPERTY(VisibleAnywhere)
		int Con = 8;
	UPROPERTY(VisibleAnywhere)
		int Int = 8;
	UPROPERTY(VisibleAnywhere)
		int Wis = 8;
	UPROPERTY(VisibleAnywhere)
		int Cha = 8;

	// Ability Modifiers
	UPROPERTY(VisibleAnywhere)
	int StrMod = -1;
	UPROPERTY(VisibleAnywhere)
	int DexMod = -1;
	UPROPERTY(VisibleAnywhere)
	int ConMod = -1;
	UPROPERTY(VisibleAnywhere)
	int IntMod = -1;
	UPROPERTY(VisibleAnywhere)
	int WisMod = -1;
	UPROPERTY(VisibleAnywhere)
	int ChaMod = -1;

	int CalculateAbilityModifier(int AbilityScore);

	void UpdateModifiers();
};
