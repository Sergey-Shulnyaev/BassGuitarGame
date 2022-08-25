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
	// ������ ��� ������ � ����������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray<class AButtonActor*>	ColumnOfOnes;
	// ������ ��� ������ � ���������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray<class AButtonActor*>	ColumnOfTwos;
	// ������ ��� ������ � ���������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray<class AButtonActor*>	ColumnOfThrees;
	// ������ ��� ������ � ������ ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	TArray<class AButtonActor*>	ColumnOfFours;

	// �������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	class USpawnComponent* SpawnComponent;

	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	class ANeck* GuitarNeck;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ������ ��� ������ ��������
	FTimerHandle SpawnOneTimer;
	// ������ ��� ������ �������
	FTimerHandle SpawnTwoTimer;
	// ������ ��� ������ �������
	FTimerHandle SpawnThreeTimer;
	// ������ ��� ������ ������ ����
	FTimerHandle SpawnFourTimer;
	
	// ��������� �� �����
	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	class ABasicPawn* PlayerPawn;

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
