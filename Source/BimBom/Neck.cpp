// Fill out your copyright notice in the Description page of Project Settings.


#include "Neck.h"
#include "ButtonActor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Actors/NeckBackground.h"
#include "Components/StringPaperFlipbookComponent.h"


// Sets default values
ANeck::ANeck()
	:
	zSpawnPointCoordinate(250),
	defaultButtonSpeed(150),
	StringNum(4),
	NeckWidth(256)
{

	float zCenter = 1024;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//root init
	myRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(myRootComponent);

	//sprite initializing
	neckSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	neckSpriteBackground->SetupAttachment(RootComponent);
	UPaperSprite* background = ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_Neck_base.SPR_Neck_base'")).Object;
	neckSpriteBackground->SetSprite(background);
	
	neckSpriteBackground->SetRelativeLocation(FVector(0, 0, zCenter));

	//play line initializing
	playLineSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlayLine"));
	playLineSprite->SetupAttachment(RootComponent);
	playLineSprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_PlayLine.SPR_PlayLine'")).Object);
	playLineSprite->SetRelativeLocation(FVector(0, 10, 0));

	//destroy lin initializing
	destroyLineSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DestroyLine"));
	destroyLineSprite->SetupAttachment(RootComponent);
	destroyLineSprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_DestroyLine.SPR_DestroyLine'")).Object);
	destroyLineSprite->SetRelativeLocation(FVector(0, 10, -20));

	//SpawnStrings
	for (int i = 1; i <= StringNum; i++)
		CreateStringAndSpawnPoint();

	SetSpawnPointsZCoordinate(1024);

}

void ANeck::CreateStringAndSpawnPoint()
{	  
	float x = -NeckWidth / 2 + (GuitarStrings.Num() + 1) * NeckWidth / (StringNum + 1);
	UStringPaperFlipbookComponent* guitarString;
	FString guitarStringName = FString("String_");
	FString numName = FString::FromInt(GuitarStrings.Num() + 1);
	guitarStringName = guitarStringName.Append(numName);
	guitarString = CreateDefaultSubobject<UStringPaperFlipbookComponent>(FName(guitarStringName));
	guitarString->SetupAttachment(RootComponent);
	guitarString->SetRelativeLocation(FVector(x, 20, 512));
	GuitarStrings.Add(guitarString);

	FVector scaleVector = FVector(0.2f, 0.2f, 0.2f);
	UStaticMeshComponent* spawnPoint;

	FString spawnPointName = FString("SpawnPoint_");
	spawnPointName = spawnPointName.Append(numName);

	spawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(FName(spawnPointName));
	spawnPoint->bHiddenInGame = true;
	spawnPoint->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	spawnPoint->SetWorldScale3D(scaleVector);
	spawnPoint->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EngineDebugMaterials/VertexColorViewMode_RedOnly.VertexColorViewMode_RedOnly'")).Object);
	spawnPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	spawnPoint->SetupAttachment(RootComponent);
	spawnPoint->SetRelativeLocation(FVector(x, 50, zSpawnPointCoordinate));
	SpawnPoints.Add(spawnPoint);
}

// Called when the game starts or when spawned
void ANeck::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ANeck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AButtonActor* ANeck::SpawnButton(int Num, FName Sound)
{
	//set location by spawn point
	FVector Location = SpawnPoints[Num-1]->GetRelativeLocation();

	FRotator Rotator = FRotator(0, 90.f, -90.f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AButtonActor* NewButtonActor = GetWorld()->SpawnActor<AButtonActor>(Location, Rotator, SpawnParameters);

	//setup relative attachment
	FAttachmentTransformRules buttonAttacnmentTransformRule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	NewButtonActor->AttachToActor(this, buttonAttacnmentTransformRule);

	NewButtonActor->SetActorRelativeLocation(Location);
	NewButtonActor->SetActorRotation(Rotator);
	NewButtonActor->SetNumber(Num);

	NewButtonActor->SetSpeed(defaultButtonSpeed);
	NewButtonActor->SetSound(Sound);

	return NewButtonActor;
}

void ANeck::SpawnBackground()
{
	//set location by spawn point
	FVector Location = FVector(0, 5, 0);
	Location.Z = SpawnPoints[0]->GetRelativeLocation().Z;

	FRotator Rotator = FRotator(0, 90.f, -90.f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ANeckBackground* back = GetWorld()->SpawnActor<ANeckBackground>(Location, Rotator, SpawnParameters);

	//setup relative attachment
	FAttachmentTransformRules buttonAttacnmentTransformRule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	back->AttachToActor(this, buttonAttacnmentTransformRule);

	back->SetActorRelativeLocation(Location);
	back->SetActorRotation(Rotator);
	back->SetSpeed(defaultButtonSpeed);	  

	back->SetLength(60 / BeatsPerMinute * defaultButtonSpeed);
	back->SetAutoDestroyTimer(GetButtonPassDistance() / defaultButtonSpeed * 1.4);
	UE_LOG(LogTemp, Log, TEXT("Spawn back %f + %f = %f"), GetWorld()->GetTimeSeconds(), 60.f / BeatsPerMinute, 60.f / BeatsPerMinute + GetWorld()->GetTimeSeconds());



	GetWorld()->GetTimerManager().SetTimer(BackSpawnTimer, this, &ANeck::SpawnBackground, 60.f / BeatsPerMinute) ;
}

void ANeck::SetSpawnPointsZCoordinate(float z)
{
	zSpawnPointCoordinate = z;
	FVector location;

	//spawn points change location
	for (int n=0; n < SpawnPoints.Num(); n++)
	{
		location = SpawnPoints[n]->GetRelativeLocation();
		location.Z = zSpawnPointCoordinate;
		SpawnPoints[n]->SetRelativeLocation(location);
	}
	
	
}

float ANeck::GetBottomBorderCoordinate()
{
	return destroyLineSprite->GetRelativeLocation().Z;
}

float ANeck::GetPlayLineCoordinate()
{
	return playLineSprite->GetRelativeLocation().Z;
}

float ANeck::GetDefaultButtonSpeed()
{
	return defaultButtonSpeed;
}

float ANeck::GetButtonPassDistance()
{
	return zSpawnPointCoordinate - GetPlayLineCoordinate()-10;
}

void ANeck::PlayString(int Num)
{
	GuitarStrings[Num-1]->PlayString();
}

void ANeck::SetBPM(int bpm)
{
	BeatsPerMinute = bpm;
}


