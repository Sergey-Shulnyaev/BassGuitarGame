// Fill out your copyright notice in the Description page of Project Settings.


#include "Neck.h"
#include "ButtonActor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/StringPaperFlipbookComponent.h"


// Sets default values
ANeck::ANeck()
	:
	zSpawnPointCoordinate(250),
	defaultButtonSpeed(100)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sprite initializing
	neckSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SetRootComponent(neckSpriteBackground);
	neckSpriteBackground->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_Neck_base.SPR_Neck_base'")).Object);

	//play line initializing
	playLineSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlayLine"));
	playLineSprite->SetupAttachment(RootComponent);
	playLineSprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_PlayLine.SPR_PlayLine'")).Object);
	playLineSprite->SetRelativeLocation(FVector(0, 10, -200));

	//destroy lin initializing
	destroyLineSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DestroyLine"));
	destroyLineSprite->SetupAttachment(RootComponent);
	destroyLineSprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_DestroyLine.SPR_DestroyLine'")).Object);
	destroyLineSprite->SetRelativeLocation(FVector(0, 10, -250));

	FVector scaleVector = FVector(0.2f, 0.2f, 0.2f);
	TArray <float> XArray = { -38, -13, 13, 38 };
	//initialising spawnpoint in bp editor for customization button spawn points
	SpawnPoint1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint1"));
	SpawnPoint1->bHiddenInGame = true;
	SpawnPoint1->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	SpawnPoint1->SetWorldScale3D(scaleVector);
	SpawnPoint1->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EngineDebugMaterials/VertexColorViewMode_RedOnly.VertexColorViewMode_RedOnly'")).Object);
	SpawnPoint1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnPoint1->SetupAttachment(RootComponent);
	SpawnPoint1->SetRelativeLocation(FVector(XArray[0], 50, zSpawnPointCoordinate));

	SpawnPoint2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint2"));
	SpawnPoint2->bHiddenInGame = true;
	SpawnPoint2->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	SpawnPoint2->SetWorldScale3D(scaleVector);
	SpawnPoint2->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EngineDebugMaterials/VertexColorViewMode_RedOnly.VertexColorViewMode_RedOnly'")).Object);
	SpawnPoint2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnPoint2->SetupAttachment(RootComponent);
	SpawnPoint2->SetRelativeLocation(FVector(XArray[1], 50, zSpawnPointCoordinate));

	SpawnPoint3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint3"));
	SpawnPoint3->bHiddenInGame = true;
	SpawnPoint3->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	SpawnPoint3->SetWorldScale3D(scaleVector);
	SpawnPoint3->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EngineDebugMaterials/VertexColorViewMode_RedOnly.VertexColorViewMode_RedOnly'")).Object);
	SpawnPoint3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnPoint3->SetupAttachment(RootComponent);
	SpawnPoint3->SetRelativeLocation(FVector(XArray[2], 50, zSpawnPointCoordinate));

	SpawnPoint4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint4"));
	SpawnPoint4->bHiddenInGame = true;
	SpawnPoint4->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	SpawnPoint4->SetWorldScale3D(scaleVector);
	SpawnPoint4->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EngineDebugMaterials/VertexColorViewMode_RedOnly.VertexColorViewMode_RedOnly'")).Object);
	SpawnPoint4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnPoint4->SetupAttachment(RootComponent);
	SpawnPoint4->SetRelativeLocation(FVector(XArray[3], 50, zSpawnPointCoordinate));

	SetSpawnPointsZCoordinate(600);

	

	GuitarString1 = CreateDefaultSubobject<UStringPaperFlipbookComponent>(FName("String1"));
	GuitarString1->SetupAttachment(RootComponent);
	GuitarString1->SetRelativeLocation(FVector(XArray[0], 20, 0));
	GuitarString1->SetRelativeScale3D(FVector(0.3, 1, 1));

	GuitarString2 = CreateDefaultSubobject<UStringPaperFlipbookComponent>(FName("String2"));
	GuitarString2->SetupAttachment(RootComponent);
	GuitarString2->SetRelativeLocation(FVector(XArray[1], 20, 0));
	GuitarString2->SetRelativeScale3D(FVector(0.3, 1, 1));

	GuitarString3 = CreateDefaultSubobject<UStringPaperFlipbookComponent>(FName("String3"));
	GuitarString3->SetupAttachment(RootComponent);
	GuitarString3->SetRelativeLocation(FVector(XArray[2], 20, 0));
	GuitarString3->SetRelativeScale3D(FVector(0.3, 1, 1));

	GuitarString4 = CreateDefaultSubobject<UStringPaperFlipbookComponent>(FName("String4"));
	GuitarString4->SetupAttachment(RootComponent);
	GuitarString4->SetRelativeLocation(FVector(XArray[3], 20, 0));
	GuitarString4->SetRelativeScale3D(FVector(0.3, 1, 1));


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
	FVector Location = FVector(0, 0, 0);
	switch (Num)
	{
	case(1):
		Location = SpawnPoint1->GetRelativeLocation();
		break;
	case(2):
		Location = SpawnPoint2->GetRelativeLocation();
		break;
	case(3):
		Location = SpawnPoint3->GetRelativeLocation();
		break;
	case(4):
		Location = SpawnPoint4->GetRelativeLocation();
		break;
	}


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

void ANeck::SetSpawnPointsZCoordinate(float z)
{
	zSpawnPointCoordinate = z;
	FVector location;

	//spawn points change location
	location = SpawnPoint1->GetRelativeLocation();
	location.Z = zSpawnPointCoordinate;
	SpawnPoint1->SetRelativeLocation(location);

	location = SpawnPoint2->GetRelativeLocation();
	location.Z = zSpawnPointCoordinate;
	SpawnPoint2->SetRelativeLocation(location);

	location = SpawnPoint3->GetRelativeLocation();
	location.Z = zSpawnPointCoordinate;
	SpawnPoint3->SetRelativeLocation(location);

	location = SpawnPoint4->GetRelativeLocation();
	location.Z = zSpawnPointCoordinate;
	SpawnPoint4->SetRelativeLocation(location);
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
	return zSpawnPointCoordinate - GetPlayLineCoordinate();
}

void ANeck::PlayString(int Num)
{
	switch (Num)
	{
	case(1):
		GuitarString1->PlayString();
		break;
	case(2):
		GuitarString2->PlayString();
		break;
	case(3):
		GuitarString3->PlayString();
		break;
	case(4):
		GuitarString4->PlayString();
		break;
	}
}


