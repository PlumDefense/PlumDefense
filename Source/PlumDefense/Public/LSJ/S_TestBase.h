#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_TestBase.generated.h"

UCLASS()
class PLUMDEFENSE_API AS_TestBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AS_TestBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(VisibleAnywhere);
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;
};
