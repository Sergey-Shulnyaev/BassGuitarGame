// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonActor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Engine/DataTable.h"


// Sets default values
AButtonActor::AButtonActor()
	:AActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Components creation
	buttonSpriteVisual = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));

	// set basic scale
	buttonSpriteVisual->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	SetRootComponent(buttonSpriteVisual);

	//load sprites datatable
	static ConstructorHelpers::FObjectFinder<UDataTable> ButtonSpriteDataObject(TEXT("DataTable'/Game/Sprites/DT_NumberSprite.DT_NumberSprite'"));
	if (ButtonSpriteDataObject.Succeeded())
	{
		SpriteDataTable = ButtonSpriteDataObject.Object;
	}

	// set default sprite
	SetNumber(1);
}

// Called when the game starts or when spawned
void AButtonActor::BeginPlay()
{
	Super::BeginPlay();
	startTime = GetWorld()->TimeSeconds;
	playTime = startTime + 4;
	endTime = startTime + 5;
}

// Called every frame
void AButtonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector WorldMoveOffset = FVector(-100.f * DeltaTime, 0.f, 0.f);
	AddActorWorldOffset(WorldMoveOffset);

}

void AButtonActor::SetNumber(int Num)
{
	//Определяет спрайт для данного buttonactor по цифре
	if (Num < 1 && Num > 4)
	{
		UE_LOG(LogTemp, Error, TEXT("NO such sprite number in ButtonActor"));
		return;
	}
	if (!SpriteDataTable)
	{		
		UE_LOG(LogTemp, Error, TEXT("NO SpriteDataTable in ButtonActor"));
		return;
	}
	FNumberSprite* ButtonSprite = nullptr;
	switch (Num)
	{
	case(1):
		ButtonSprite = SpriteDataTable->FindRow<FNumberSprite>(FName(TEXT("1")), FString(TEXT("Dialogue Context")), true);
		break;
	case(2):
		ButtonSprite = SpriteDataTable->FindRow<FNumberSprite>(FName(TEXT("2")), FString(TEXT("Dialogue Context")), true);
		break;
	case(3):
		ButtonSprite = SpriteDataTable->FindRow<FNumberSprite>(FName(TEXT("3")), FString(TEXT("Dialogue Context")), true);
		break;
	case(4):
		ButtonSprite = SpriteDataTable->FindRow<FNumberSprite>(FName(TEXT("4")), FString(TEXT("Dialogue Context")), true);
		break;

	}
	if (!ButtonSprite)
	{
		UE_LOG(LogTemp, Error, TEXT("NO ButtonSprite in SpriteDataTable in ButtonActor"));
		return;
	}
	buttonSpriteVisual->SetSprite(ButtonSprite->Sprite);

}
