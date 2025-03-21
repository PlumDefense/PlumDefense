#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_Enemy.generated.h"

UCLASS()
class PLUMDEFENSE_API AS_Enemy : public AActor
{
	GENERATED_BODY()

public:
	AS_Enemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(VisibleAnywhere);
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

private:
	UPROPERTY(VisibleAnywhere)
	float Speed;

	UPROPERTY(VisibleAnywhere)
	int32 HP;

	UPROPERTY(VisibleAnywhere)
	int32 DEF;

};