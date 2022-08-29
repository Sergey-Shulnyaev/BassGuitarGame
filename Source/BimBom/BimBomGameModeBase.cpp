// Copyright Epic Games, Inc. All Rights Reserved.


#include "BimBomGameModeBase.h"
#include "BimBomPlayerController.h"
#include "BasicPawn.h"
#include "ButtonActor.h"
#include "Neck.h"
#include "Kismet/GameplayStatics.h"

ABimBomGameModeBase::ABimBomGameModeBase()
	:
	BottomBorderCoordinate(250),
	DeltaPlay(20),
	BeatsPerMinute(120),
	CurrentButtonIndex(0)
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

	//load sprites datatable
	static ConstructorHelpers::FObjectFinder<UDataTable> ButtonSpriteDataObject(
		TEXT("DataTable'/Game/Songs/DT_ButtonSpawn_TEST1.DT_ButtonSpawn_TEST1'"));

	if (ButtonSpriteDataObject.Succeeded())
	{
		SongDataTable = ButtonSpriteDataObject.Object;
		ButtonRowNames = SongDataTable->GetRowNames();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO SONG DATATABLE"));
	}
}

void ABimBomGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// spawner initializing
	GuitarNeck = GetGuitarNeckFromScene();
	if (!GuitarNeck)
	{
		UE_LOG(LogTemp, Error, TEXT("No Neck Spawn Actor"));
		return;
	}

	// set bottom border by getting relative coordinate
	BottomBorderCoordinate = -GuitarNeck->GetBottomBorderCoordinate();

	// set play line 
	PlayLineCoordinate = -GuitarNeck->GetPlayLineCoordinate();
	// set song start time
	StartSongTime = GetWorld()->GetTimeSeconds();
	// set default button speed
	DefaultButtonSpeed = GuitarNeck->GetDefaultButtonSpeed();
	// set button pass 
	ButtonDistance = GuitarNeck->GetButtonPassDistance();

	SetSpawnTimer();
	
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
	CheckLastButtons();
}

void ABimBomGameModeBase::CheckLastButtons()
{
	for (int i = 0; i < 4; i++)
	{
		if (QueuesOfButtons[i].Queue.Num() > 0)
		{
			AButtonActor *Button = QueuesOfButtons[i].Queue[0];
			// get button relative location
			FVector locat = GuitarNeck->GetActorLocation() - Button->GetActorLocation();
			/*UE_LOG(LogTemp, Log, TEXT("Name: %s, X:%f, Y:%f, Z:%f"), 
				*Button->GetName(), locat.X, locat.Y, locat.Z);*/
			if (locat.X > BottomBorderCoordinate)
			{
				QueuesOfButtons[i].Queue.RemoveAt(0);
				Button->CustomDestroy();
			}
		}
	}
}

void ABimBomGameModeBase::SetSpawnTimer()
{
	if (!SongDataTable)
		return;
	//getting spawn parameters
	FButtonSpawnParameters *buttonSpawnParameters = SongDataTable->FindRow<FButtonSpawnParameters>(
		ButtonRowNames[CurrentButtonIndex], FString(TEXT("Dialogue Context")), true);
	float buttonPlayTime = buttonSpawnParameters->Time;
	float currentTime = GetWorld()->GetTimeSeconds() - StartSongTime;
	float playTime = buttonPlayTime / BeatsPerMinute * 60 - ButtonDistance / DefaultButtonSpeed;
	float deltaSpawnTime = playTime - currentTime;

	UE_LOG(LogTemp, Log, TEXT("Delta Spawn Time = %f"), deltaSpawnTime);

	if (deltaSpawnTime < 0.05f)
	// instante spawn button 
	{
		SpawnButton();
		if (deltaSpawnTime < -0.05f)
			UE_LOG(LogTemp, Warning, TEXT("Bad Time Spawn below zero"));
	}
	else
	{
		// Creation delegate with parameter
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ABimBomGameModeBase::SpawnButton);

		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, TimerDelegate, deltaSpawnTime, false);
	}
}

void ABimBomGameModeBase::SpawnButton()
{
	FButtonSpawnParameters* buttonSpawnParameters = SongDataTable->FindRow<FButtonSpawnParameters>(
		ButtonRowNames[CurrentButtonIndex], FString(TEXT("Dialogue Context")), true);
	
	// if fret not in range
	if (buttonSpawnParameters->Fret < 1 || buttonSpawnParameters->Fret > 4)
	{
		UE_LOG(LogTemp, Error, TEXT("Button with index: %d fret not in range"), CurrentButtonIndex);
		CurrentButtonIndex += 1;
		SetSpawnTimer();
		return;
	}
	// Spawn button via Neck
	AButtonActor* Button = GuitarNeck->SpawnButton(buttonSpawnParameters->Fret);
	// Add Button in queue
	QueuesOfButtons[buttonSpawnParameters->Fret - 1].Queue.Add(Button);
	
	CurrentButtonIndex += 1;
	if (CurrentButtonIndex > ButtonRowNames.Num()-1)
	{
		UE_LOG(LogTemp, Log, TEXT("Song ended"));
		return;
	}
	SetSpawnTimer();
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

	FVector locat = GuitarNeck->GetActorLocation() - Button->GetActorLocation();
	// if button can be destroyed
	if (locat.X > PlayLineCoordinate - DeltaPlay)
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


