// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonActor.h"
#include "Spawner.generated.h"

class AButtonActor;

UCLASS()
class BIMBOM_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// спавнит кнопку и возвращает указатель на неё
	AButtonActor* SpawnButton(int Num);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
