// Fill out your copyright notice in the Description page of Project Settings.


#include "Neck.h"
#include "ButtonActor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

// Sets default values
ANeck::ANeck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sprite initialising
	neckSpriteBackground = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SetRootComponent(neckSpriteBackground);
	neckSpriteBackground->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_Neck_base.SPR_Neck_base'")).Object);

	//play line initialisin
	playLineSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlayLine"));
	playLineSprite->SetupAttachment(RootComponent);
	playLineSprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>
		(TEXT("PaperSprite'/Game/Sprites/SPR_PlayLine.SPR_PlayLine'")).Object);
	playLineSprite->SetRelativeLocation(FVector(0, 10, -200));

	FVector scaleVector = FVector(0.2f, 0.2f, 0.2f);
	//initialising spawnpoint in bp editor for customization button spawn points
	SpawnPoint1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint1"));
	SpawnPoint1->bHiddenInGame = true;
	SpawnPoint1->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	SpawnPoint1->SetWorldScale3D(scaleVector);
	SpawnPoint1->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EngineDebugMaterials/VertexColorViewMode_RedOnly.VertexColorViewMode_RedOnly'")).Object);
	SpawnPoint1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnPoint1->SetupAttachment(RootComponent);
	SpawnPoint1->SetRelativeLocation(FVector(-38, 10, 250));

	SpawnPoint2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint2"));
	SpawnPoint2->bHiddenInGame = true;
	SpawnPoint2->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	SpawnPoint2->SetWorldScale3D(scaleVector);
	SpawnPoint2->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EngineDebugMaterials/VertexColorViewMode_RedOnly.VertexColorViewMode_RedOnly'")).Object);
	SpawnPoint2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnPoint2->SetupAttachment(RootComponent);
	SpawnPoint2->SetRelativeLocation(FVector(-13, 10, 250));

	SpawnPoint3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint3"));
	SpawnPoint3->bHiddenInGame = true;
	SpawnPoint3->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	SpawnPoint3->SetWorldScale3D(scaleVector);
	SpawnPoint3->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EngineDebugMaterials/VertexColorViewMode_RedOnly.VertexColorViewMode_RedOnly'")).Object);
	SpawnPoint3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnPoint3->SetupAttachment(RootComponent);
	SpawnPoint3->SetRelativeLocation(FVector(13, 10, 250));

	SpawnPoint4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint4"));
	SpawnPoint4->bHiddenInGame = true;
	SpawnPoint4->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	SpawnPoint4->SetWorldScale3D(scaleVector);
	SpawnPoint4->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EngineDebugMaterials/VertexColorViewMode_RedOnly.VertexColorViewMode_RedOnly'")).Object);
	SpawnPoint4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnPoint4->SetupAttachment(RootComponent);
	SpawnPoint4->SetRelativeLocation(FVector(38, 10, 250));
}

// Called when the game starts or when spawned
void ANeck::BeginPlay()
{
	Super::BeginPlay();
	//setSpawnPointsOnTop();
}

//void ANeck::setSpawnPointsOnTop()
//{
//	FIntPoint ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();
//	UE_LOG(LogTemp, Log, TEXT("ViewportSize = (%d, %d)"), ViewportSize.X, ViewportSize.Y);
//}

// Called every frame
void ANeck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AButtonActor* ANeck::SpawnButton(int Num)
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
	return NewButtonActor;
}

