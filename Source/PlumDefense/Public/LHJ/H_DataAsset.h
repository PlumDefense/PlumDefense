// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "H_DataAsset.generated.h"

USTRUCT(Atomic,BlueprintType)
struct FH_DataAsset : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 EnemyCount;	// 라운드 당 생성할 마리수
	UPROPERTY(EditAnywhere)
	int32 KillGold;		// 처치 골드
	UPROPERTY(EditAnywhere)
	int32 EnemyHealth;	// Enemy 체력
	UPROPERTY(EditAnywhere)
	int32 TowerDamage;	// 타워 데미지
	UPROPERTY(EditAnywhere)
	float TowerRange;	// 타워 공격 범위
	UPROPERTY(EditAnywhere)
	float TowerAttackDelay;	// 타워 공격 주기
};
#pragma once
