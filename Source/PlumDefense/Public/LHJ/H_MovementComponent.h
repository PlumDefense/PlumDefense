// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "H_MovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLUMDEFENSE_API UH_MovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UH_MovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	virtual void SetupInputBinding(class UEnhancedInputComponent* input);
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	class AH_User* user;

private: // Move
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* IA_Move;
	void F_Move(const struct FInputActionValue& Value);

private: // Mouse
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* IA_Mouse;
	void F_Turn(const struct FInputActionValue& Value);
};
