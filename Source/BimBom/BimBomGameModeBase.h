// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "BimBomGameModeBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FQueueButtonActors
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Queue)
	TArray<class AButtonActor*> Queue;
};

USTRUCT(BlueprintType)
struct FButtonSpawnParameters : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	FName Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	int String;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	int Speed;
};

USTRUCT(BlueprintType)
struct FSongData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Song)
	class UDataTable* SoundsDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Song)
	class USoundBase* Music;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Song)
	float BeatsPerMinute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	class UDataTable* ButtonSpawnDataTable;
};

USTRUCT(BlueprintType)
struct FSoundsData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	class USoundBase* Sound;

};

UCLASS()
class BIMBOM_API ABimBomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	ABimBomGameModeBase();
	
protected:
	//Array of queues
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray<FQueueButtonActors> QueuesOfButtons;

	// Neck
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	class ANeck* GuitarNeck;


	// button spawn DataTable
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	class UDataTable* ButtonSpawnDataTable;
	// row names to get propper button parameters
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray <FName> ButtonRowNames;
	// BPM
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	float BeatsPerMinute;
	// song start time
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	float StartSongTime;
	// If a button below border -> destroy the button 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	float BottomBorderCoordinate;
	// If a button below play line - delta play -> can be played
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	float PlayLineCoordinate;
	// distance which button pass to play
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	float ButtonDistance;
	// button default speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	float DefaultButtonSpeed;
	// current button index
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	int CurrentButtonIndex;
	// data load error
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	bool bError;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Array of timer for spawn ButtonActor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray<FTimerHandle> SpawnTimerArray;

	//SpawnTimer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	FTimerHandle SpawnTimer;
	
	// Pointer of Scene Pawn
	UPROPERTY(BlueprintReadOnly, Category = Pawn)
	class ABasicPawn* PlayerPawn;

	// Search for Neck via Scene
	UFUNCTION(BlueprintCallable, Category = Spawner)
	class ANeck* GetGuitarNeckFromScene();
	
	// Check last first buttons of queues and destroy them if they are out of the range
	UFUNCTION(BlueprintCallable, Category = Spawner)
	void CheckLastButtons();

	//sounds dictionary
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	TMap<FName, USoundBase*> SoundsDictionary;
	
	//main song
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	USoundBase* MainSong;
	
	//delay for start playing song in seconds
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	float SongDelay;
	
	//PlaySongTimer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	FTimerHandle PlaySongTimer;

	// start play
	UFUNCTION(BlueprintCallable, Category = Sound)
	void StartPlayingSong();
public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// If a button below border -> destroy the button 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	float DeltaPlay;
	
	UFUNCTION(BlueprintCallable, Category = Spawner)
	void SetSpawnTimer();

	UFUNCTION(BlueprintCallable, Category = Spawner)
	void SpawnButton();

	UFUNCTION(BlueprintCallable, Category = Destroyer)
	void DestroyButton(int Num);
	};
