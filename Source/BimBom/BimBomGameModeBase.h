// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Array of timer for spawn ButtonActor
	TArray<FTimerHandle> SpawnTimerArray;
	
	// Pointer of Pawn
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

	UFUNCTION(BlueprintCallable, Category = Spawner)
	void SpawnButton(int Num);

	UFUNCTION(BlueprintCallable, Category = Destroyer)
	void DestroyButton(int Num);
	};
