// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "H_PathFinding.generated.h"

struct FNode;

UCLASS()
class PLUMDEFENSE_API AH_PathFinding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AH_PathFinding();

	// 레벨에 있는 Grid를 참조하기 위한 변수.
	// Grid.h의 UCLASS 안에 BlueprintType을 넣어줘야 작동함.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	class AH_Grid* Grid;

	// 시작점
	UPROPERTY(EditAnywhere)
	AActor* Seeker;

	// 도착점
	UPROPERTY(EditAnywhere)
	AActor* Target;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 경로 찾기
	void FindPath(const FVector& StartPos, const FVector& TargetPos);

	// H값(현재 노드 - 도착 노드) 거리 구하는 함수
	int GetDistance(FNode* NodeA, FNode* NodeB);

	// FindPath 함수가 실행된 후, 최종 경로를 구하는 함수
	void RetracePath(FNode* StartNode, FNode* EndNode);
};