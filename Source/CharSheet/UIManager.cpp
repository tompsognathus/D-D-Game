// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "CharacterCreatorWidget.h"

// Sets default values for this component's properties
UUIManager::UUIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Create UI widgets	
	CharacterCreatorWidget = CreateDefaultSubobject<UCharacterCreatorWidget>(TEXT("CharacterCreatorWidget"));


}


// Called when the game starts
void UUIManager::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UUIManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

