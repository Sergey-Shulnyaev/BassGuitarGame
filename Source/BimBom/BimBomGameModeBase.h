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
	int Tone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	int Fret;
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

	// BPM
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	float BeatsPerMinute;

	// song DataTable
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	class UDataTable* SongDataTable;

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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Array of timer for spawn ButtonActor
	TArray<FTimerHandle> SpawnTimerArray;
	
	// Pointer of Scene Pawn
	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	class ABasicPawn* PlayerPawn;

	// Search for Neck via Scene
	UFUNCTION(BlueprintCallable, Category = Spawner)
	class ANeck* GetGuitarNeckFromScene();
	
	// Check last first buttons of queues and destroy them if they are out of the range
	UFUNCTION(BlueprintCallable, Category = Spawner)
	void CheckLastButtons();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// If a button below border -> destroy the button 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	float DeltaPlay;

	UFUNCTION(BlueprintCallable, Category = Spawner)
	void SpawnButton(int Num);

	UFUNCTION(BlueprintCallable, Category = Destroyer)
	void DestroyButton(int Num);
	};
