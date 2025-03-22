// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "H_User.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindingDelegate, class UEnhancedInputComponent*)

UCLASS()
class PLUMDEFENSE_API AH_User : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AH_User();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* IMC_Player;
public:
	FInputBindingDelegate InputBindingDelegate; // 인풋 바인딩용
	
private:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere)
	class UH_MovementComponent* MovementComponent;
	UPROPERTY(VisibleAnywhere)
	class UH_BuildComponent* BuildComponent;
	
};
