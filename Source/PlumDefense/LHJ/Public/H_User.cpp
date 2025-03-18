// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/H_User.h"

// Sets default values
AH_User::AH_User()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

