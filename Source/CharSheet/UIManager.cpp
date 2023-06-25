// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "Adventurer.h"
#include "CharacterCreatorWidget.h"


// Sets default values for this component's properties
UUIManager::UUIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UUIManager::BeginPlay()
{
	Super::BeginPlay();

	GetAdventurerReference();
	CreateAndDisplayCharacterCreatorWidget();

}


// Called every frame
void UUIManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UUIManager::CreateAndDisplayCharacterCreatorWidget()
{
	if (CharacterCreatorWidgetRef) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		CharacterCreatorWidget = CreateWidget<UUserWidget>(GetWorld(), CharacterCreatorWidgetRef);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (CharacterCreatorWidget)
		{
			//let add it to the view port
			CharacterCreatorWidget->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot add CharacterCreatorWidget to Viewport"));
		}
		//Show the Cursor.
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterCreatorWidgetRef on UIManager not set in blueprint"));
	}
}

void UUIManager::GetAdventurerReference()
{
	if (GetOuter() && GetOuter()->IsA<AActor>())
	{
		AActor* OwnerActor = Cast<AActor>(GetOuter());
		Adventurer = OwnerActor->FindComponentByClass<UAdventurer>();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't get Adventurer reference"));
	}
}

