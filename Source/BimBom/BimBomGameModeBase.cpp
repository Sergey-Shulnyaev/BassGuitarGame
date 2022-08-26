// Copyright Epic Games, Inc. All Rights Reserved.


#include "BimBomGameModeBase.h"
#include "BimBomPlayerController.h"
#include "BasicPawn.h"
#include "SpawnComponent.h"
#include "ButtonActor.h"
#include "Neck.h"
#include "Kismet/GameplayStatics.h"

ABimBomGameModeBase::ABimBomGameModeBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = ABasicPawn::StaticClass();
	PlayerControllerClass = ABimBomPlayerController::StaticClass();

	// ������������� ��������
	SpawnComponent = CreateDefaultSubobject<USpawnComponent>(TEXT("Spawn Component"));

	GuitarNeck = nullptr;

}

void ABimBomGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// ������������� ��������
	GuitarNeck = GetGuitarNeckFromScene();

	for (int i = 1; i < 5; i++)
		SpawnButton(i);
}

ANeck* ABimBomGameModeBase::GetGuitarNeckFromScene()
{
	TArray<AActor*> actorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANeck::StaticClass(), actorsToFind);
	}
	for (AActor* neckActor : actorsToFind)

	{

		//Is this Actor of type ANeck class?
		ANeck* neck = Cast<ANeck>(neckActor);
		if (neck)
		{
			return neck;
		}
	}
	return nullptr;
}

void ABimBomGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABimBomGameModeBase::SpawnButton(int Num)
{
	if (!GuitarNeck)
	{
		UE_LOG(LogTemp, Error, TEXT("No Neck Spawn Actor"));
		return;
	}
	AButtonActor* Button = GuitarNeck->SpawnButton(Num);
	// �������� ������� � ���������� ��� �������
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ABimBomGameModeBase::SpawnButton, Num);

	// ������ ��������� � ���������� ������ �������� �� ��� 
	switch (Num)
	{
	case(1):
		ColumnOfOnes.Add(Button);
		GetWorld()->GetTimerManager().SetTimer(SpawnOneTimer, TimerDelegate, Num, false);
		break;
	case(2):
		ColumnOfTwos.Add(Button);
		GetWorld()->GetTimerManager().SetTimer(SpawnTwoTimer, TimerDelegate, Num, false);
		break;
	case(3):
		ColumnOfThrees.Add(Button);
		GetWorld()->GetTimerManager().SetTimer(SpawnThreeTimer, TimerDelegate, Num, false);
		break;
	case(4):
		ColumnOfFours.Add(Button);
		GetWorld()->GetTimerManager().SetTimer(SpawnFourTimer, TimerDelegate, Num, false);
		break;
	}
		

	
}

void ABimBomGameModeBase::DestroyButton(int Num)
{
	AButtonActor* Button = nullptr;
	// �������� ���� �� ������
	switch (Num)
	{
	case(1):
		if (ColumnOfOnes.Num() > 0)
			Button = ColumnOfOnes[0];
		break;
	case(2):
		if (ColumnOfTwos.Num() > 0)
			Button = ColumnOfTwos[0];
		break;
	case(3):
		if (ColumnOfThrees.Num() > 0)
			Button = ColumnOfThrees[0];
		break;
	case(4):
		if (ColumnOfFours.Num() > 0)
			Button = ColumnOfFours[0];
		break;
	}

	//���� ������ �������, ��
	if (Button)
	{
		//����� �� � ����������
		if (Button->GetCanBeDestroyed())
		{
			//�� - �����������
			switch (Num)
			{
			case(1):
				ColumnOfOnes.RemoveAt(0);
				break;
			case(2):
				ColumnOfTwos.RemoveAt(0);
				break;
			case(3):
				ColumnOfThrees.RemoveAt(0);
				break;
			case(4):
				ColumnOfFours.RemoveAt(0);			
				break;
			}
			Button->Destroy();
		}
		else
			//��� - ���� �����
		{
			UE_LOG(LogTemp, Warning, TEXT("BIDLO RANO Num %d"), Num);
		}
	}
	
}


