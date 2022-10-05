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

	//Root component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* myRootComponent;

	// ��������� ��� ������������
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

	//spawn point with visualizing
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpawnPoint1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpawnPoint2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpawnPoint3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawn, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpawnPoint4;

	//string init
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Play, meta = (AllowPrivateAccess = "true"))
	class UStringPaperFlipbookComponent* GuitarString1_1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Play, meta = (AllowPrivateAccess = "true"))
	class UStringPaperFlipbookComponent* GuitarString2_1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Play, meta = (AllowPrivateAccess = "true"))
	class UStringPaperFlipbookComponent* GuitarString3_1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Play, meta = (AllowPrivateAccess = "true"))
	class UStringPaperFlipbookComponent* GuitarString4_1;

	//SpawnTimer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	FTimerHandle BackSpawnTimer;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Play, meta = (AllowPrivateAccess = "true"))
	//class UStringPaperFlipbookComponent* GuitarString1_2;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Play, meta = (AllowPrivateAccess = "true"))
	//class UStringPaperFlipbookComponent* GuitarString2_2;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Play, meta = (AllowPrivateAccess = "true"))
	//class UStringPaperFlipbookComponent* GuitarString3_2;	
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Play, meta = (AllowPrivateAccess = "true"))
	//class UStringPaperFlipbookComponent* GuitarString4_2;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Spawn)
	class AButtonActor* SpawnButton(int Num, FName Sound);

	UFUNCTION(BlueprintCallable, Category = Spawn)
	void SpawnBackground();

	//delete?
	UFUNCTION(BlueprintCallable, Category = Spawn)
	void SetSpawnPointsZCoordinate(float z); 

	UFUNCTION(BlueprintCallable, Category = Spawn)
	float GetBottomBorderCoordinate();

	UFUNCTION(BlueprintCallable, Category = Spawn)
	float GetPlayLineCoordinate();

	UFUNCTION(BlueprintCallable, Category = Spawn)
	float GetDefaultButtonSpeed();

	// get distance which button should go through
	UFUNCTION(BlueprintCallable, Category = Spawn)
	float GetButtonPassDistance();

	UFUNCTION(BlueprintCallable, Category = Spawn)
	void PlayString(int Num);
};
