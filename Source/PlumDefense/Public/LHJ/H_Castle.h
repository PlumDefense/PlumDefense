// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "H_Castle.generated.h"

UCLASS()
class PLUMDEFENSE_API AH_Castle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AH_Castle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 외형 
public:
	UPROPERTY(VisibleAnyWhere)
	class UStaticMeshComponent* CastleMesh;
	UPROPERTY(VisibleAnyWhere)
	class UBoxComponent* CastleCollision;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 체력
public:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxHealth = 10;

private:
	UPROPERTY(visibleanywhere)
	int32 Health;
	void DecreateHealth();
};
