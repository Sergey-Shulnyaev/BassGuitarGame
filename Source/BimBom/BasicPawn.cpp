// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPawn.h"
#include "ButtonActor.h"
#include "BimBomGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasicPawn::ABasicPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent->SetRelativeRotation(FRotator(0, 0, 0));
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Components creation
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	GameCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));

	// Setup Camera
	GameCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	GameCamera->SetOrthoWidth(1024);
	GameCamera->SetAspectRatio(16 / 9);

	GameCamera->SetRelativeRotation(FRotator(-90, 0, 0));
	GameCamera->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABasicPawn::BeginPlay()
{
	Super::BeginPlay();

	GameMode = GetWorld()->GetAuthGameMode<ABimBomGameModeBase>();
	
}

// Called every frame
void ABasicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Declaring an action binding
	FInputActionBinding ActionBindingPlayFirstString = FInputActionBinding("StringOneAction", IE_Pressed);
	FInputActionBinding ActionBindingPlaySecondString = FInputActionBinding("StringTwoAction", IE_Pressed);
	FInputActionBinding ActionBindingPlayThirdString = FInputActionBinding("StringThreeAction", IE_Pressed);
	FInputActionBinding ActionBindingPlayFourthString = FInputActionBinding("StringFourAction", IE_Pressed);

	//Creating a handler which binds to the given function with a fixed int parameter
	FInputActionHandlerSignature FirstStringActionHandler;
	FInputActionHandlerSignature SecondStringActionHandler;
	FInputActionHandlerSignature ThirdStringActionHandler;
	FInputActionHandlerSignature FourthStringActionHandler;

	//Binding the function named PlayString to our handlers
	//The first parameter (this) means that the handler will search the given function inside the current class
	FirstStringActionHandler.BindUFunction(this, FName("PlayString"), 1);
	SecondStringActionHandler.BindUFunction(this, FName("PlayString"), 2);
	ThirdStringActionHandler.BindUFunction(this, FName("PlayString"), 3);
	FourthStringActionHandler.BindUFunction(this, FName("PlayString"), 4);

	//Associating our action binding with our new delegate
	ActionBindingPlayFirstString.ActionDelegate = FirstStringActionHandler;
	ActionBindingPlaySecondString.ActionDelegate = SecondStringActionHandler;
	ActionBindingPlayThirdString.ActionDelegate = ThirdStringActionHandler;
	ActionBindingPlayFourthString.ActionDelegate = FourthStringActionHandler;


	//Performing the actual binding...
	PlayerInputComponent->AddActionBinding(ActionBindingPlayFirstString);
	PlayerInputComponent->AddActionBinding(ActionBindingPlaySecondString);
	PlayerInputComponent->AddActionBinding(ActionBindingPlayThirdString);
	PlayerInputComponent->AddActionBinding(ActionBindingPlayFourthString);

}

void ABasicPawn::PlayString(int Num)
{
	// ABimBomGameModeBase::DestroyButton
	//StringPlayEvent.Broadcast(Num);
	GameMode->DestroyButton(Num);
}

