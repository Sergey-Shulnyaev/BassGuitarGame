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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* neckSpriteBackground;

	//play line
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* playLineSprite;

	//destroyLine
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* destroyLineSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	float zSpawnPointCoordinate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	float defaultButtonSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	float playTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Play, meta = (AllowPrivateAccess = "true"))
	float endTime;

	//spawn point with visualizing
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpawnPoint1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpawnPoint2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpawnPoint3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpawnPoint4;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Spawn)
	class AButtonActor* SpawnButton(int Num);

	//delete?
	UFUNCTION(BlueprintCallable, Category = Spawn)
	void SetSpawnPointsZCoordinate(float z);

	UFUNCTION(BlueprintCallable, Category = Spawn)
	float GetDefaultButtonPlayTime();

	UFUNCTION(BlueprintCallable, Category = Spawn)
	void SetDefaultButtonPlayTime(float time);

	UFUNCTION(BlueprintCallable, Category = Spawn)
	float GetDefaultButtonDestroyTime();

	UFUNCTION(BlueprintCallable, Category = Spawn)
	void SetDefaultButtonDestroyTime(float time);  

	UFUNCTION(BlueprintCallable, Category = Spawn)
	float GetBottomBorder();
};
