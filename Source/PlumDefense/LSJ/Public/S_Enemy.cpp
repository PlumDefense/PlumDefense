// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/S_Enemy.h"

// Sets default values
AS_Enemy::AS_Enemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AS_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AS_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

