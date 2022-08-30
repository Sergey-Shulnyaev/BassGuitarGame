// Copyright Epic Games, Inc. All Rights Reserved.


#include "BimBomGameModeBase.h"
#include "BimBomPlayerController.h"
#include "BasicPawn.h"
#include "ButtonActor.h"
#include "Neck.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

ABimBomGameModeBase::ABimBomGameModeBase()
	:
	BottomBorderCoordinate(250),
	DeltaPlay(20),
	BeatsPerMinute(80),
	CurrentButtonIndex(0),
	bError(false)
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

	/** LOAD DATA **/
	//load all songs datatable
	FSongData* SongData = nullptr;
	static ConstructorHelpers::FObjectFinder<UDataTable> SongsDataObject(
		TEXT("DataTable'/Game/Songs/DT_Songs.DT_Songs'"));

	if (SongsDataObject.Succeeded())
	{
		SongData = SongsDataObject.Object->FindRow<FSongData>(FName("FurTree"), FString(TEXT("Dialogue Context")), true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO SONG DATATABLE"));
	}

	//load sounds datatable
	if (SongData)
	{
		if (SongData->SoundsDataTable)
		{
			UDataTable* SoundsData = SongData->SoundsDataTable;

			for (const auto SoundRowName : SoundsData->GetRowNames())
			{
				USoundBase* CurrentSound = SoundsData->FindRow<FSoundsData>(
					SoundRowName, FString(TEXT("Dialogue Context")), true)->Sound;
				SoundsDictionary.Add(SoundRowName, CurrentSound);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("NO SOUNDS DATA TABLE"));
			bError = true;
		}
	}
	//load button spawn datatable
	if (SongData)
	{
		if (SongData->ButtonSpawnDataTable)
		{
			ButtonSpawnDataTable = SongData->ButtonSpawnDataTable;
			ButtonRowNames = ButtonSpawnDataTable->GetRowNames();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("NO BUTTON SPAWN DATATABLE"));
			bError = true;
		}
	}
	
	
	if (SongData)
	{
		// music load
		if (SongData->Music)
			MainSong = SongData->Music;
		else
			bError = true;
		//BPM
		if (SongData->BeatsPerMinute)
			BeatsPerMinute = SongData->BeatsPerMinute;
		else
			bError = true;
		SongDelay = 6;
	}
	



}

void ABimBomGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	// if has building error then dont start spawn
	if (bError)
		return;

	//music start
	GetWorld()->GetTimerManager().SetTimer(PlaySongTimer, this, &ABimBomGameModeBase::StartPlayingSong, SongDelay);

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

void ABimBomGameModeBase::StartPlayingSong()
{
	UGameplayStatics::PlaySound2D(this, MainSong);
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
	if (!ButtonSpawnDataTable)
		return;
	//getting spawn parameters
	FButtonSpawnParameters *buttonSpawnParameters = ButtonSpawnDataTable->FindRow<FButtonSpawnParameters>(
		ButtonRowNames[CurrentButtonIndex], FString(TEXT("Dialogue Context")), true);
	float buttonPlayTime = buttonSpawnParameters->Time;
	float currentTime = GetWorld()->GetTimeSeconds() - StartSongTime;
	float playTime = buttonPlayTime / BeatsPerMinute * 60 - ButtonDistance / DefaultButtonSpeed;
	float deltaSpawnTime = playTime - currentTime + SongDelay;

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
	FButtonSpawnParameters* buttonSpawnParameters = ButtonSpawnDataTable->FindRow<FButtonSpawnParameters>(
		ButtonRowNames[CurrentButtonIndex], FString(TEXT("Dialogue Context")), true);
	
	// if fret not in range
	if (buttonSpawnParameters->String < 1 || buttonSpawnParameters->String > 4)
	{
		UE_LOG(LogTemp, Error, TEXT("Button with index: %d fret not in range"), CurrentButtonIndex);
		CurrentButtonIndex += 1;
		SetSpawnTimer();
		return;
	}
	// Spawn button via Neck
	AButtonActor* Button = GuitarNeck->SpawnButton(buttonSpawnParameters->String, buttonSpawnParameters->Sound);
	// Add Button in queue
	QueuesOfButtons[buttonSpawnParameters->String - 1].Queue.Add(Button);
	
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
	//UGameplayStatics::PlaySound2D(this, E5);
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
		UGameplayStatics::PlaySound2D(this, *SoundsDictionary.Find(Button->GetSound()));
		Button->Destroy();
	}
	else
	{
		//negative sanctions for player
		UE_LOG(LogTemp, Warning, TEXT("BIDLO RANO Num %d"), Num);
	}
}


