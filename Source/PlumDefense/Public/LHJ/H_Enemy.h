// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "H_Enemy.generated.h"

UCLASS()
class PLUMDEFENSE_API AH_Enemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AH_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;
	
private:
	UPROPERTY(VisibleAnywhere)
	float MoveSpeed;
	UPROPERTY(VisibleAnywhere)
	int32 Health;
};
