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
	neckSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	neckSpriteBackground->SetupAttachment(RootComponent);
	UPaperSprite* background = ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_Background.SPR_Background'")).Object;
	neckSpriteBackground->SetSprite(background);

}

// Called when the game starts or when spawned
void ANeckBackground::BeginPlay()
{
	Super::BeginPlay();
	
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