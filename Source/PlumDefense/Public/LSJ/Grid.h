#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

USTRUCT(Atomic)
struct FNode {
	GENERATED_USTRUCT_BODY()

public:
	bool bWalkable;
	FVector WorldPosition;

	FNode* Parent;

	int GridX;
	int GridY;

	int GCost;
	int HCost;
	int FCost() { return GCost + HCost; }

	FNode() {
		bWalkable = true;
		WorldPosition = FVector(0, 0, 0);
		Parent = nullptr;

		GridX = 0;
		GridY = 0;
	}

	FNode(bool _walkable, FVector _worldPos, int _gridX, int _gridY) {
		bWalkable = _walkable;
		WorldPosition = _worldPos;

		GridX = _gridX;
		GridY = _gridY;
	}

	bool operator==(const FNode& Other) const {
		return WorldPosition == Other.WorldPosition;
	}
};

FORCEINLINE uint32 GetTypeHash(const FNode& Node) {
	return GetTypeHash(Node.WorldPosition);
}

USTRUCT(Atomic)
struct FGridRow {
	GENERATED_USTRUCT_BODY()
	TArray<FNode*> Nodes;
};

UCLASS()
class PLUMDEFENSE_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AGrid();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere)
	float NodeRadius;
	UPROPERTY()
	TArray<FGridRow> Grid;

	UPROPERTY()
	int GridSizeX = 10;
	UPROPERTY()
	int GridSizeY = 10;
	UPROPERTY()
	float NodeDiameter;
	UPROPERTY()
	float GridWorldSizeX;
	UPROPERTY()
	float GridWorldSizeY;

public:
	// �ڽ� �ݸ���
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	TArray<FNode*> Path;

	UFUNCTION(BlueprintCallable)
	void CreateGrid();

	FNode* NodeFromWorldPoint(const FVector& worldPosition);

	bool IsWalkable(const FVector& WorldPoint);

	TArray<FNode*> GetNeighbours(FNode* Node);

	UFUNCTION()
	void DrawDebugGrid();

};
