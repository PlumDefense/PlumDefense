#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

USTRUCT(Atomic)
struct FSNode {
	GENERATED_USTRUCT_BODY()

public:
	bool bWalkable;
	FVector WorldPosition;

	FSNode* Parent;

	int GridX;
	int GridY;

	int GCost;
	int HCost;
	int FCost() { return GCost + HCost; }

	FSNode() {
		bWalkable = true;
		WorldPosition = FVector(0, 0, 0);
		Parent = nullptr;

		GridX = 0;
		GridY = 0;
	}

	FSNode(bool _walkable, FVector _worldPos, int _gridX, int _gridY) {
		bWalkable = _walkable;
		WorldPosition = _worldPos;

		GridX = _gridX;
		GridY = _gridY;
	}

	bool operator==(const FSNode& Other) const {
		return WorldPosition == Other.WorldPosition;
	}
};

FORCEINLINE uint32 GetTypeHash(const FSNode& Node) {
	return GetTypeHash(Node.WorldPosition);
}

USTRUCT(Atomic)
struct FSGridRow {
	GENERATED_USTRUCT_BODY()
	TArray<FSNode*> Nodes;
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
	TArray<FSGridRow> Grid;

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
	// 박스 콜리전
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	TArray<FSNode*> Path;

	UFUNCTION(BlueprintCallable)
	void CreateGrid();

	FSNode* NodeFromWorldPoint(const FVector& worldPosition);

	bool IsWalkable(const FVector& WorldPoint);

	TArray<FSNode*> GetNeighbours(FSNode* Node);

	UFUNCTION()
	void DrawDebugGrid();

};
