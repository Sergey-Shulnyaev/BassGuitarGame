// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ButtonActor.h"
#include "SpawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BIMBOM_API USpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// спавнит кнопку и возвращает указатель на неё
	AButtonActor* SpawnButton(int Num);
};
