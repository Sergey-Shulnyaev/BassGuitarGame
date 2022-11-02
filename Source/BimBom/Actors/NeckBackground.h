// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NeckBackground.generated.h"

UCLASS()
class BIMBOM_API ANeckBackground : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANeckBackground();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Root component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* myRootComponent;

	// Компонент для визуализации
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* neckUpLineSpriteBackground;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* neckFirstMidLineSpriteBackground;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* neckSecondMidLineSpriteBackground;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* neckThirdMidLineSpriteBackground;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* neckDownLineSpriteBackground;

	// actor speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Play)
	float speed;

	//AutoDestroyTimer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	FTimerHandle DestroyTimer;

	void AutoDestroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//set get speed
	UFUNCTION(BlueprintCallable, Category = Play)
	float GetSpeed();
	UFUNCTION(BlueprintCallable, Category = Play)
	void SetSpeed(float velocity);
	UFUNCTION(BlueprintCallable, Category = Play)
	void SetLength(float length);
	UFUNCTION(BlueprintCallable, Category = Play)
	void SetAutoDestroyTimer(float time);
};
