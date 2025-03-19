// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/LHJ/H_User.h"

#include "Camera/CameraComponent.h"
#include "LHJ/H_MovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "LHJ/H_BuildComponent.h"

// Sets default values
AH_User::AH_User()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetRelativeLocation(FVector(0, 0, 60));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;

	MovementComponent = CreateDefaultSubobject<UH_MovementComponent>(TEXT("MovementComponent"));
	BuildComponent = CreateDefaultSubobject<UH_BuildComponent>(TEXT("BuildComponent"));

	ConstructorHelpers::FObjectFinder<UInputMappingContext> tmpIMC(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Player.IMC_Player'"));
	if (tmpIMC.Succeeded())
		IMC_Player = tmpIMC.Object;
}

// Called when the game starts or when spawned
void AH_User::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AH_User::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AH_User::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (auto pc = GetWorld()->GetFirstPlayerController())
	{
		auto LocalPlayer = pc->GetLocalPlayer();
		if (auto ss = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			ss->AddMappingContext(IMC_Player, 1);
		}
	}
	
	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (input)
	{
		InputBindingDelegate.Broadcast(input);
	}
}
