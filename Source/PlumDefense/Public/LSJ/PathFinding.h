#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathFinding.generated.h"

struct FSNode;
class AGrid;

UCLASS()
class PLUMDEFENSE_API APathFinding : public AActor
{
	GENERATED_BODY()
	
public:	
	APathFinding();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	AGrid* Grid;

	UPROPERTY(EditAnywhere)
	AActor* Seeker;

	UPROPERTY(EditAnywhere)
	AActor* Target;

public:
	void FindPath(const FVector& StartPos, const FVector& TargetPos);

	int GetDistance(FSNode* NodeA, FSNode* NodeB);

	void RetracePath(FSNode* StartNode, FSNode* EndNode);

};
