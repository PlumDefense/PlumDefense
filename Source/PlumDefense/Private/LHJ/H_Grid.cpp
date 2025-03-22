// Fill out your copyright notice in the Description page of Project Settings.


#include "LHJ/H_Grid.h"

#include "Components/BoxComponent.h"

// Sets default values
AH_Grid::AH_Grid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
}

// Called when the game starts or when spawned
void AH_Grid::BeginPlay()
{
	Super::BeginPlay();
	
	NodeDiameter = NodeRadius * 2;
	FVector origin;
	FVector boxExtent;
	GetActorBounds(false, origin, boxExtent);

	GridWorldSizeX = boxExtent.X * 2;
	GridWorldSizeY = boxExtent.Y * 2;

	GridSizeX = FMath::RoundToInt(GridWorldSizeX / NodeDiameter);
	GridSizeY = FMath::RoundToInt(GridWorldSizeY / NodeDiameter);

	CreateGrid();
}

// Called every frame
void AH_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugGrid();
}

void AH_Grid::CreateGrid()
{
	Grid.SetNum(GridSizeX);
	FVector WorldBottomLeft = GetActorLocation() - FVector(GridWorldSizeX / 2, GridWorldSizeY / 2, 0);

	for (int x = 0; x < GridSizeX; x++) {
		Grid[x].Nodes.SetNum(GridSizeY);

		for (int y = 0; y < GridSizeY; y++) {
			FVector WorldPoint = WorldBottomLeft + FVector(x * NodeDiameter + NodeRadius, y * NodeDiameter + NodeRadius, 0);
			bool bWalkable = IsWalkable(WorldPoint);
			Grid[x].Nodes[y] = new FNode(bWalkable, WorldPoint, x, y);
		}
	}
}

FNode* AH_Grid::NodeFromWorldPoint(const FVector& worldPosition)
{
	float PercentX = (worldPosition.X + GridWorldSizeX / 2) / GridWorldSizeX;
	float PercentY = (worldPosition.Y + GridWorldSizeY / 2) / GridWorldSizeY;

	PercentX = FMath::Clamp(PercentX, 0.0f, 1.0f);
	PercentY = FMath::Clamp(PercentY, 0.0f, 1.0f);

	int x = FMath::Floor(GridSizeX * PercentX);
	int y = FMath::Floor(GridSizeY * PercentY);

	return Grid[x].Nodes[y];
}

bool AH_Grid::IsWalkable(const FVector& WorldPoint) {
	TArray<FOverlapResult> OverlapResults;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(NodeRadius);

	bool bHit = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		WorldPoint,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		CollisionShape
	);

	return OverlapResults.Num() == 0;
}

TArray<FNode*> AH_Grid::GetNeighbours(FNode* Node)
{
	TArray<FNode*> Neighbours;

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0) continue;

			int CheckX = Node->GridX + x;
			int CheckY = Node->GridY + y;

			if (0 <= CheckX && CheckX < GridSizeX && 0 <= CheckY && CheckY < GridSizeY) {
				Neighbours.Emplace(Grid[CheckX].Nodes[CheckY]);
			}
		}
	}

	return Neighbours;
}

void AH_Grid::DrawDebugGrid() {

	FNode* PlayerNode = NodeFromWorldPoint(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());

	for (int x = 0; x < GridSizeX; x++) {
		for (int y = 0; y < GridSizeY; y++) {
			FNode* Node = Grid[x].Nodes[y];
			FColor NodesColor = Node->bWalkable ? FColor::Green : FColor::Red;
			if (!Path.IsEmpty()) {
				if (Path.Contains(Node)) {
					NodesColor = FColor::Black;
				}
			}
			if (Node == PlayerNode) {
				NodesColor = FColor::Cyan;
			}
			DrawDebugBox(
				GetWorld(),
				Node->WorldPosition,
				FVector(NodeRadius - 10, NodeRadius - 10, NodeRadius - 10),
				NodesColor,
				false,
				-1.f,
				0,
				10.f
			);
		}
	}
}