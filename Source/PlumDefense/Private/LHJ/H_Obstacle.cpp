// Fill out your copyright notice in the Description page of Project Settings.


#include "LHJ/H_Obstacle.h"

#include "Components/BoxComponent.h"

// Sets default values
AH_Obstacle::AH_Obstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(50));
	RootComponent = BoxCollision;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AH_Obstacle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AH_Obstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
