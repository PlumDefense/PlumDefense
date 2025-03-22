// Fill out your copyright notice in the Description page of Project Settings.


#include "LHJ/H_Enemy.h"

#include "Components/BoxComponent.h"

// Sets default values
AH_Enemy::AH_Enemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(50));
	BoxCollision->SetRelativeScale3D(FVector(.6));
	RootComponent = BoxCollision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CastleMesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
	Mesh->SetupAttachment(RootComponent);

	Tags.Add("Enemy");
}

// Called when the game starts or when spawned
void AH_Enemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AH_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
