// Fill out your copyright notice in the Description page of Project Settings.


#include "LHJ/H_MovementComponent.h"

#include "LHJ/H_User.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// Sets default values for this component's properties
UH_MovementComponent::UH_MovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	ConstructorHelpers::FObjectFinder<UInputAction> tmpMove(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Move.IA_Move'"));
	if (tmpMove.Succeeded())
		IA_Move = tmpMove.Object;
	ConstructorHelpers::FObjectFinder<UInputAction> tmpLook(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Look.IA_Look'"));
	if (tmpLook.Succeeded())
		IA_Mouse = tmpLook.Object;
}


// Called when the game starts
void UH_MovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UH_MovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
	if (GetOwner())
	{
		user = Cast<AH_User>(GetOwner());
		if (user)
		{
			user->InputBindingDelegate.AddUObject(this, &UH_MovementComponent::SetupInputBinding);
		}
	}
}

void UH_MovementComponent::SetupInputBinding(UEnhancedInputComponent* input)
{
	input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &UH_MovementComponent::F_Move);
	input->BindAction(IA_Mouse, ETriggerEvent::Triggered, this, &UH_MovementComponent::F_Turn);
}


// Called every frame
void UH_MovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UH_MovementComponent::F_Move(const struct FInputActionValue& Value)
{
	FVector2D v = Value.Get<FVector2D>();
	
	FVector direction(v.X, v.Y, 0);
	user->AddMovementInput(user->GetTransform().TransformVector(direction));
}

void UH_MovementComponent::F_Turn(const struct FInputActionValue& Value)
{
	FVector2D v = Value.Get<FVector2D>();
	user->AddControllerYawInput(v.X);
	user->AddControllerPitchInput(v.Y);
}
