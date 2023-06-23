// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UUIManager::UUIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Create UI widgets
	SpawnWidget(TEXT("Blueprint'/Game/WBP_CharacterSheet.WBP_CharacterSheet_C'"), CharConfiguratorWidgetInstance);
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


void UUIManager::SpawnWidget(FString Path, UUserWidget* UserWidgetOUT)
{
	// Get the world
	UWorld* World = GetWorld();

	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();

		if (PlayerController)
		{
			UClass* WidgetClass = LoadClass<UUserWidget>(NULL, *Path);

			if (WidgetClass)
			{
				UserWidgetOUT = CreateWidget<UUserWidget>(PlayerController, WidgetClass);

				UE_LOG(LogTemp, Display, TEXT("UserWidgetOUT = %s"), *UserWidgetOUT->GetName())
				if (UserWidgetOUT)
				{
					UserWidgetOUT->AddToViewport();
				}
			}
		}
	}
}