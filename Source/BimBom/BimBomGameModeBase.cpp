// Copyright Epic Games, Inc. All Rights Reserved.


#include "BimBomGameModeBase.h"
#include "BimBomPlayerController.h"
#include "BasicPawn.h"
#include "SpawnComponent.h"
#include "ButtonActor.h"
#include "Neck.h"
#include "Kismet/GameplayStatics.h"

ABimBomGameModeBase::ABimBomGameModeBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = ABasicPawn::StaticClass();
	PlayerControllerClass = ABimBomPlayerController::StaticClass();

	//initializing of ANeck
	GuitarNeck = nullptr;

	//initializing of queues
	for (int i = 1; i < 5; i++)
	{
		FQueueButtonActors queueStruct;
		QueuesOfButtons.Add(queueStruct);
	}

	//initializing of timers
	for (int i = 1; i < 5; i++)
	{
		FTimerHandle timer;
		SpawnTimerArray.Add(timer);
	}
}

void ABimBomGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// инициализация спавнера
	GuitarNeck = GetGuitarNeckFromScene();

	for (int i = 1; i < 5; i++)
		SpawnButton(i);
}

ANeck* ABimBomGameModeBase::GetGuitarNeckFromScene()
{
	//initializing array for possible ANeck
	TArray<AActor*> actorsToFind;
	//getting all actors
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANeck::StaticClass(), actorsToFind);
	}
	// finding ANeck
	for (AActor* neckActor : actorsToFind)

	{

		//Is this Actor of type ANeck class?
		ANeck* neck = Cast<ANeck>(neckActor);
		if (neck)
		{
			return neck;
		}
	}
	return nullptr;
}

void ABimBomGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABimBomGameModeBase::CheckLastButtons()
{

}

void ABimBomGameModeBase::SpawnButton(int Num)
{
	// check ANeck
	if (!GuitarNeck)
	{
		UE_LOG(LogTemp, Error, TEXT("No Neck Spawn Actor"));
		return;
	}
	// Spawn button via Neck
	AButtonActor* Button = GuitarNeck->SpawnButton(Num);
	// Creation delegate with parameter
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ABimBomGameModeBase::SpawnButton, Num);

	// Add Button in queue
	QueuesOfButtons[Num - 1].Queue.Add(Button);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerArray[Num-1], TimerDelegate, Num, false);
}

void ABimBomGameModeBase::DestroyButton(int Num)
{
	AButtonActor* Button = nullptr;
	// Check existence of button
	if (QueuesOfButtons[Num - 1].Queue.Num() > 0)
		Button = QueuesOfButtons[Num - 1].Queue[0];

	// if button doesn't exist
	if (!Button)
	{
		UE_LOG(LogTemp, Error, TEXT("NO BUTTON NUM %d"), Num);
		return;
	}

	// if button can be destroyed
	if (Button->GetCanBeDestroyed())
	{
		//destroy
		QueuesOfButtons[Num - 1].Queue.RemoveAt(0);
		Button->Destroy();
	}
	else
	{
		//negative sanctions for player
		UE_LOG(LogTemp, Warning, TEXT("BIDLO RANO Num %d"), Num);
	}
}


