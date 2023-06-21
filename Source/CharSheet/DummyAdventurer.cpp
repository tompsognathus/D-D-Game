// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyAdventurer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "CharSheetCharacter.h"

// Sets default values
ADummyAdventurer::ADummyAdventurer()
{
	AdventurerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Adventurer"));
	AdventurerMesh->SetupAttachment(RootComponent);

	AdventurerWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	AdventurerWeaponMesh->SetupAttachment(AdventurerMesh, "index_01_r");
	AdventurerWeaponMesh->bForceNavigationObstacle = false;
	

	SpringArm = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(AdventurerMesh);
	const FTransform ArmTransform = FTransform(
		FRotator(0.f, -90.f, 0.f),
		FVector(0.f, 0.f, 30.f),
		FVector(1.f));
	SpringArm->SetRelativeTransform(ArmTransform);

	RenderTarget = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("RenderTarget"));
	RenderTarget->SetupAttachment(SpringArm);


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADummyAdventurer::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
if (World)
	{
		ACharSheetCharacter* Player = Cast<ACharSheetCharacter>(World->GetFirstPlayerController()->GetPawn());

		if (Player)
		{
			if (Player->GetMesh()->SkeletalMesh)
			{
				AdventurerMesh->SetSkeletalMesh(Player->GetMesh()->SkeletalMesh);
				if (Player->GetMesh()->GetAnimInstance()->GetClass())
				{
					AdventurerMesh->SetAnimInstanceClass(Player->GetMesh()->GetAnimInstance()->GetClass());
				}
			}
		}
	}
}

// Called every frame
void ADummyAdventurer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

