// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BimBomGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BIMBOM_API ABimBomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	ABimBomGameModeBase();
	
protected:
	// Массив для работы с единичками
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray<class AButtonActor*>	ColumnOfOnes;
	// Массив для работы с двоечками
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray<class AButtonActor*>	ColumnOfTwos;
	// Массив для работы с троечками
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray<class AButtonActor*>	ColumnOfThrees;
	// Массив для работы с четвер очками
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray<class AButtonActor*>	ColumnOfFours;

	// Спавнер
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	class USpawnComponent* SpawnComponent;

	// Гриф
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	class ANeck* GuitarNeck;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Таймер для спавна единичек
	FTimerHandle SpawnOneTimer;
	// Таймер для спавна двоечек
	FTimerHandle SpawnTwoTimer;
	// Таймер для спавна троечек
	FTimerHandle SpawnThreeTimer;
	// Таймер для спавна четвер очек
	FTimerHandle SpawnFourTimer;
	
	// Указатель на Пешку
	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	class ABasicPawn* PlayerPawn;

	// Ищет ANeck на всей сцене
	UFUNCTION(BlueprintCallable, Category = Spawner)
	class ANeck* GetGuitarNeckFromScene();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Spawner)
	void SpawnButton(int Num);

	UFUNCTION(BlueprintCallable, Category = Destroyer)
	void DestroyButton(int Num);
};
