// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "H_BuildComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLUMDEFENSE_API UH_BuildComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UH_BuildComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	virtual void SetupInputBinding(class UEnhancedInputComponent* input);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	class AH_User* user;

private: // Build
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* IA_Build;
	void F_Build();

	bool bCanBuild;
	FTransform BuildTransform;

	void PreviewBuild();

	UPROPERTY()
	class UCameraComponent* UserCamera;
	UPROPERTY()
	class UStaticMeshComponent* PreviewMesh;
	UPROPERTY()
	class UMaterialInterface* MI_Preview_True;
	UPROPERTY()
	class UMaterialInterface* MI_Preview_False;

private: // Placement
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* IA_Placement;
	void F_Place();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> PlaceTower;

	bool bCanPlace;

private: // Rotation
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* IA_RotateBuild;
	void F_Rotation();
	void F_EndRotation();
	
	FRotator BuildRotation;

	FTimerHandle TimerHandle_Rotation;

private: // Destroy
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* IA_Destroy;
	void F_Destroy();
	void F_EndDestroy();

	bool bCanDestroy;
	UPROPERTY()
	class AActor* DestroyActor;
	UPROPERTY()
	class UMaterialInterface* MI_Destroy;

	// 포탑의 높이
	float PreviewMeshHalfHeight;
};
