#include "LSJ/PathFinding.h"
#include "Components/BoxComponent.h"
#include "LSJ/Grid.h"

#include "Components/StaticMeshComponent.h"

APathFinding::APathFinding()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APathFinding::BeginPlay()
{
	Super::BeginPlay();
	
}

void APathFinding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Seeker&Target �˻�
	if (!Seeker || !Target) return;
	FindPath(Seeker->GetActorLocation(), Target->GetActorLocation());
}

void APathFinding::FindPath(const FVector& StartPos, const FVector& TargetPos)
{
	FSNode* StartNode = Grid->NodeFromWorldPoint(StartPos);
	FSNode* TargetNode = Grid->NodeFromWorldPoint(TargetPos);

	TArray<FSNode*> OpenSet;
	TSet<FSNode*> ClosedSet;
	OpenSet.Emplace(StartNode);

	while (OpenSet.Num() > 0) {
		// OpenSet���� FCost�� ���� �����鼭, HCost ���� ���� ���
		FSNode* CurrentNode = OpenSet[0];
		for (int i = 0; i < OpenSet.Num(); i++) {
			if (
				OpenSet[i]->FCost() < CurrentNode->FCost() ||
				(OpenSet[i]->FCost() == CurrentNode->FCost() && OpenSet[i]->HCost < CurrentNode->HCost)
				) {
				CurrentNode = OpenSet[i];
			}
		}
		OpenSet.Remove(CurrentNode);
		ClosedSet.Emplace(CurrentNode);

		if (CurrentNode == TargetNode) {
			RetracePath(StartNode, TargetNode);
			return;
		}

		for (FSNode* Neighbour : Grid->GetNeighbours(CurrentNode)) {
			if (!Neighbour->bWalkable || ClosedSet.Contains(Neighbour)) continue;

			int NewMovementCostToNeighbour = CurrentNode->GCost + GetDistance(CurrentNode, Neighbour);
			if (NewMovementCostToNeighbour < Neighbour->GCost || !OpenSet.Contains(Neighbour)) {
				Neighbour->GCost = NewMovementCostToNeighbour;
				Neighbour->HCost = GetDistance(Neighbour, TargetNode);
				Neighbour->Parent = CurrentNode;

				if (!OpenSet.Contains(Neighbour)) OpenSet.Emplace(Neighbour);

			}

		}

	}
}

int APathFinding::GetDistance(FSNode* NodeA, FSNode* NodeB) {

	int DstX = abs(NodeA->GridX - NodeB->GridX);
	int DstY = abs(NodeA->GridY - NodeB->GridY);

	if (DstX > DstY)
		return 14 * DstY + 10 * (DstX - DstY);
	return 14 * DstX + 10 * (DstY - DstX);
}

void APathFinding::RetracePath(FSNode* StartNode, FSNode* EndNode) {

	Grid->Path.Empty();
	FSNode* CurrentNode = EndNode;

	while (CurrentNode != StartNode) {
		Grid->Path.Emplace(CurrentNode);
		if (!CurrentNode->Parent) {
			UE_LOG(LogTemp, Warning, TEXT("Parent is nullptr"));
			return;
		}
		CurrentNode = CurrentNode->Parent;
	}
	Grid->Path.Emplace(StartNode);

	Algo::Reverse(Grid->Path);

}