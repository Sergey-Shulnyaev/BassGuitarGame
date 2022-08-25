// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "ButtonActor.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();	
	AButtonActor* NewButtonActor = SpawnButton(3);
}

AButtonActor* ASpawner::SpawnButton(int Num)
{
	FVector Location = FVector(100, 100, 100);
	FRotator Rotator = FRotator(0, 90.f, -90.f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AButtonActor* NewButtonActor = GetWorld()->SpawnActor<AButtonActor>(Location, Rotator, SpawnParameters);
	NewButtonActor->SetNumber(3);
	return NewButtonActor;
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

