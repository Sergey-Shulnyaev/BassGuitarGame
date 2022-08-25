// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"	   
#include "BasicPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStringPlayEvent, int, Num);

UCLASS()
class BIMBOM_API ABasicPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn")
	class UCameraComponent* GameCamera;

	UFUNCTION(BlueprintCallable, Category = "Strings")
	void PlayString(int Num);

	UPROPERTY(BlueprintAssignable, Category = "Strings")
	FStringPlayEvent StringPlayEvent;
};
