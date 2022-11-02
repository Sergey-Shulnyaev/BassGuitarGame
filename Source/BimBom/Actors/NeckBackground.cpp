// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NeckBackground.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

// Sets default values
ANeckBackground::ANeckBackground()
	:
	speed(100.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sprite initializing
	/*neckSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	neckSpriteBackground->SetupAttachment(RootComponent);
	UPaperSprite* background = ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_Background.SPR_Background'")).Object;
	neckSpriteBackground->SetSprite(background);*/

	//root init
	myRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(myRootComponent);

	UPaperSprite* background;
	neckUpLineSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("UpLine"));
	neckUpLineSpriteBackground->SetupAttachment(RootComponent);
	background = ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_back_up_line.SPR_back_up_line'")).Object;
	neckUpLineSpriteBackground->SetSprite(background);

	/*neckFirstMidLineSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FirstMidLine"));
	neckFirstMidLineSpriteBackground->SetupAttachment(RootComponent);
	background = ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_back_mid_line.SPR_back_mid_line'")).Object;
	neckFirstMidLineSpriteBackground->SetSprite(background);*/

	neckSecondMidLineSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SecondMidLine"));
	neckSecondMidLineSpriteBackground->SetupAttachment(RootComponent);
	background = ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_back_mid_line.SPR_back_mid_line'")).Object;
	neckSecondMidLineSpriteBackground->SetSprite(background);

	/*neckThirdMidLineSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ThirdMidLine"));
	neckThirdMidLineSpriteBackground->SetupAttachment(RootComponent);
	background = ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_back_mid_line.SPR_back_mid_line'")).Object;
	neckThirdMidLineSpriteBackground->SetSprite(background);*/

	neckDownLineSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DownLine"));
	neckDownLineSpriteBackground->SetupAttachment(RootComponent);
	background = ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_back_down_line.SPR_back_down_line'")).Object;
	neckDownLineSpriteBackground->SetSprite(background);

	SetLength(75.f);
}

// Called when the game starts or when spawned
void ANeckBackground::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANeckBackground::AutoDestroy()
{
	Destroy();
}

// Called every frame
void ANeckBackground::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector WorldMoveOffset = FVector(-1.f * speed * DeltaTime, 0.f, 0.f);
	AddActorWorldOffset(WorldMoveOffset);
}

float ANeckBackground::GetSpeed()
{
	return speed;
}

void ANeckBackground::SetSpeed(float velocity)
{
	speed = velocity;  
}

void ANeckBackground::SetLength(float length)
{
	neckUpLineSpriteBackground->SetRelativeLocation(FVector(0, 0, length));
	//neckFirstMidLineSpriteBackground->SetRelativeLocation(FVector(0, 0, length / 4 * 3));
	neckSecondMidLineSpriteBackground->SetRelativeLocation(FVector(0, 0, length / 4 * 2));
	//neckThirdMidLineSpriteBackground->SetRelativeLocation(FVector(0, 0, length / 4));
	neckDownLineSpriteBackground->SetRelativeLocation(FVector(0, 0, 0));
}

void ANeckBackground::SetAutoDestroyTimer(float time)
{
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &ANeckBackground::AutoDestroy, time);
}



