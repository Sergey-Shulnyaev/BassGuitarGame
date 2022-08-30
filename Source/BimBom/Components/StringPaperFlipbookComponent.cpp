// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StringPaperFlipbookComponent.h"
#include "PaperFlipbook.h"

UStringPaperFlipbookComponent::UStringPaperFlipbookComponent()
:
	UPaperFlipbookComponent()
{
	FlipbookIdle = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("PaperFlipbook'/Game/Sprites/String/PFB_String_Idle.PFB_String_Idle'")).Object;
	FlipbookPlay = ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("PaperFlipbook'/Game/Sprites/String/PFB_String.PFB_String'")).Object;
	SetFlipbook(FlipbookIdle);
	
}

void UStringPaperFlipbookComponent::StopPlayString()
{
	SetFlipbook(FlipbookIdle);
}

void UStringPaperFlipbookComponent::PlayString()
{
	
	SetFlipbook(FlipbookPlay);
	GetWorld()->GetTimerManager().SetTimer(EndPlayTimer, this,
		&UStringPaperFlipbookComponent::StopPlayString, FlipbookPlay->GetNumFrames() / FlipbookPlay->GetFramesPerSecond()-0.05);
}
