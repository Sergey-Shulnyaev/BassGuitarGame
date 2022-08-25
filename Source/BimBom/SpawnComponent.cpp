// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponent.h"

// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();
}

AButtonActor* USpawnComponent::SpawnButton(int Num)
{
	FVector Location = FVector(100, 200 * (Num - 3), 100);
	FRotator Rotator = FRotator(0, 90.f, -90.f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AButtonActor* NewButtonActor = GetWorld()->SpawnActor<AButtonActor>(Location, Rotator, SpawnParameters);
	NewButtonActor->SetNumber(Num);
	return NewButtonActor;
}

