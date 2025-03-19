// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/LHJ/H_Castle.h"

#include "Components/BoxComponent.h"

// Sets default values
AH_Castle::AH_Castle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CastleCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CastleCollision"));
	CastleCollision->SetBoxExtent(FVector(50));
	RootComponent = CastleCollision;

	CastleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CastleMesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> CastleMeshAsset(
		TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (CastleMeshAsset.Succeeded())
	{
		CastleMesh->SetStaticMesh(CastleMeshAsset.Object);
	}
	CastleMesh->SetupAttachment(RootComponent);

	Tags.Add("Castle");
}

// Called when the game starts or when spawned
void AH_Castle::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}

// Called every frame
void AH_Castle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
