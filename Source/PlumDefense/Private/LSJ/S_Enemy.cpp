#include "../../Public/LSJ/S_Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

AS_Enemy::AS_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (CubeMesh.Succeeded()) {
		MeshComp->SetStaticMesh(CubeMesh.Object);
	}
	MeshComp->SetupAttachment(BoxComp);

}

void AS_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AS_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}