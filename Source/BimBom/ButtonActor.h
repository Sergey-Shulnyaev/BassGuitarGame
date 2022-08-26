// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ButtonActor.generated.h"

USTRUCT(BlueprintType)
struct FNumberSprite : public FTableRowBase
{
	GENERATED_BODY()
public:

	/** ссылка на спрайт для текущего RowNumber **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperSprite *Sprite;
};

UCLASS()
class BIMBOM_API AButtonActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// sprite number
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	int spriteNumber;

	// Компонент для визуализации
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* buttonSpriteVisual;

	// DataTable где указаны все возможные спрайты, от 1 до 4
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UDataTable* SpriteDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Play, meta = (AllowPrivateAccess = "true"))
	float startTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Play, meta = (AllowPrivateAccess = "true"))
	float playTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Play, meta = (AllowPrivateAccess = "true"))
	float endTime;

	// Таймер автоматического удаления
	FTimerHandle AutoDestroyTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// change sprite(number on sprite)
	void SetNumber(int Num);

	// destroy with additional functionality
	void CustomDestroy();

};
