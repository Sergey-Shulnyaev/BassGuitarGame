// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "StringPaperFlipbookComponent.generated.h"

/**
 * 
 */
UCLASS()
class BIMBOM_API UStringPaperFlipbookComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()

public:

	UStringPaperFlipbookComponent();

protected:
	// timer to set flipbook in idle from play
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timer")
	FTimerHandle EndPlayTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Play")
	class UPaperFlipbook* FlipbookIdle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Play")
	class UPaperFlipbook* FlipbookPlay;

	UFUNCTION(BlueprintCallable, Category = "Play")
	void StopPlayString();

public:
	UFUNCTION(BlueprintCallable, Category = "Play")
	void PlayString();
};
