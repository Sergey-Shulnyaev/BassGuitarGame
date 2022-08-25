// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Neck.generated.h"

UCLASS()
class BIMBOM_API ANeck : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANeck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Компонент для визуализации
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* neckSpriteBackground;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	TArray<FVector> spawnPoints;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Spawn)
	class AButtonActor* SpawnButton(int Num);

	

	
};
