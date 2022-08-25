// Fill out your copyright notice in the Description page of Project Settings.


#include "Neck.h"
#include "ButtonActor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

// Sets default values
ANeck::ANeck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	neckSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SetRootComponent(neckSpriteBackground);
	neckSpriteBackground->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_Neck_base.SPR_Neck_base'")).Object);
}

// Called when the game starts or when spawned
void ANeck::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANeck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AButtonActor* ANeck::SpawnButton(int Num)
{
	//костыль надо сделать трансформацию по углу
	FVector Location = FVector(-65 + 27 * Num, -60, 100);
	FRotator Rotator = FRotator(0, 90.f, -90.f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AButtonActor* NewButtonActor = GetWorld()->SpawnActor<AButtonActor>(Location, Rotator, SpawnParameters);

	//setup relative attachment
	FAttachmentTransformRules buttonAttacnmentTransformRule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	NewButtonActor->AttachToActor(this, buttonAttacnmentTransformRule);

	NewButtonActor->SetActorRelativeLocation(Location);
	NewButtonActor->SetActorRotation(Rotator);
	NewButtonActor->SetNumber(Num);
	return NewButtonActor;
}

