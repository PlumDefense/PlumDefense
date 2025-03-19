// Fill out your copyright notice in the Description page of Project Settings.


#include "LHJ/H_BuildComponent.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

#include "Camera/CameraComponent.h"
#include "LHJ/H_User.h"
#include "PlumDefense.h"

UH_BuildComponent::UH_BuildComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	ConstructorHelpers::FObjectFinder<UInputAction> tmpBuild(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Build.IA_Build'"));
	if (tmpBuild.Succeeded())
		IA_Build = tmpBuild.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> tmpPlace(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Placement.IA_Placement'"));
	if (tmpPlace.Succeeded())
		IA_Placement = tmpPlace.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> tmpRotation(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_RotateBuild.IA_RotateBuild'"));
	if (tmpRotation.Succeeded())
		IA_RotateBuild = tmpRotation.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> tmpDestroy(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Destroy.IA_Destroy'"));
	if (tmpDestroy.Succeeded())
		IA_Destroy = tmpDestroy.Object;
}


// Called when the game starts
void UH_BuildComponent::BeginPlay()
{
	Super::BeginPlay();

	UserCamera = user->GetComponentByClass<UCameraComponent>();

	PreviewMesh = Cast<UStaticMeshComponent>(user->AddComponentByClass(UStaticMeshComponent::StaticClass(), true,
	                                                                   FTransform(FRotator(0, 0, 0), FVector(0, 0, 0),
		                                                                   FVector(1, 1, 1)),
	                                                                   false));

	// Static Mesh 설정
	UStaticMesh* SM_Preview = LoadObject<UStaticMesh>(
		nullptr, TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (SM_Preview)
	{
		PreviewMesh->SetStaticMesh(SM_Preview);
		PreviewMesh->SetVisibility(false);
		PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	MI_Preview_True = LoadObject<UMaterialInterface>(
		nullptr, TEXT(
			"/Script/Engine.MaterialInstanceConstant'/Game/Blueprints/LHJ/Mat/MI_Preview_True.MI_Preview_True'"));

	MI_Preview_False = LoadObject<UMaterialInterface>(
		nullptr, TEXT(
			"/Script/Engine.MaterialInstanceConstant'/Game/Blueprints/LHJ/Mat/MI_Preview_False.MI_Preview_False'"));
}

void UH_BuildComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetOwner())
	{
		user = Cast<AH_User>(GetOwner());
		if (user)
		{
			user->InputBindingDelegate.AddUObject(this, &UH_BuildComponent::SetupInputBinding);
		}
	}
}

void UH_BuildComponent::SetupInputBinding(class UEnhancedInputComponent* input)
{
	input->BindAction(IA_Build, ETriggerEvent::Started, this, &UH_BuildComponent::F_Build);
	input->BindAction(IA_Placement, ETriggerEvent::Started, this, &UH_BuildComponent::F_Place);
	input->BindAction(IA_RotateBuild, ETriggerEvent::Started, this, &UH_BuildComponent::F_Rotation);
	input->BindAction(IA_RotateBuild, ETriggerEvent::Completed, this, &UH_BuildComponent::F_EndRotation);
	input->BindAction(IA_Destroy, ETriggerEvent::Triggered, this, &UH_BuildComponent::F_Destroy);
	input->BindAction(IA_Destroy, ETriggerEvent::Completed, this, &UH_BuildComponent::F_EndDestroy);
}


// Called every frame
void UH_BuildComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCanBuild)
		PreviewBuild();
}

void UH_BuildComponent::F_Build()
{
	bCanBuild = !bCanBuild;
	if (bCanBuild)
		PreviewMesh->SetVisibility(true);
	else
		PreviewMesh->SetVisibility(false);
}

void UH_BuildComponent::PreviewBuild()
{
	FHitResult outHit;
	FVector start = UserCamera->GetComponentLocation();
	FVector end = start + UserCamera->GetForwardVector() * 1000;
	FCollisionQueryParams params;
	params.AddIgnoredActor(user);
	bool bHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, params);
	if (bHit)
	{
		BuildTransform.SetLocation(outHit.Location);
		BuildTransform.SetRotation(BuildRotation.Quaternion());
		BuildTransform.SetScale3D(FVector(1));
		PreviewMesh->SetWorldTransform(BuildTransform);
		PreviewMesh->SetMaterial(0, MI_Preview_True);
		bCanPlace = true;
		// LOG_S(Warning, TEXT("Hit: %s"), *outHit.GetActor()->GetName());
	}
	else
	{
		BuildTransform.SetLocation(end);
		BuildTransform.SetRotation(BuildRotation.Quaternion());
		BuildTransform.SetScale3D(FVector(1));
		PreviewMesh->SetWorldTransform(BuildTransform);
		PreviewMesh->SetMaterial(0, MI_Preview_False);
		bCanPlace = false;
	}
}

void UH_BuildComponent::F_Place()
{
	if (!bCanPlace) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = user;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto placeActor = GetWorld()->SpawnActor<AActor>(PlaceTower, BuildTransform, SpawnParams);
	if (placeActor)
		placeActor->Tags.Add("Buildable");
}

void UH_BuildComponent::F_Rotation()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Rotation, [&]()
	{
		BuildRotation = BuildTransform.GetRotation().Rotator() + FRotator(0, 5, 0);
	}, 0.1, true);
}

void UH_BuildComponent::F_EndRotation()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Rotation);
	TimerHandle_Rotation = FTimerHandle();
}

void UH_BuildComponent::F_Destroy()
{
	FHitResult outHit;
	FVector start = UserCamera->GetComponentLocation();
	FVector end = start + UserCamera->GetForwardVector() * 1000;
	FCollisionQueryParams params;
	params.AddIgnoredActor(user);
	bool bHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, params);

	if (bHit && outHit.GetActor()->ActorHasTag("Buildable"))
	{
		if (DestroyActor->IsValidLowLevel() && DestroyActor != outHit.GetActor())
		{
			UStaticMeshComponent* MeshComponent = DestroyActor->FindComponentByClass<UStaticMeshComponent>();
			if (MeshComponent)
			{
				MeshComponent->SetMaterial(0, MI_Destroy);
			}
		}

		DestroyActor = outHit.GetActor();

		UStaticMeshComponent* MeshComponent = DestroyActor->FindComponentByClass<UStaticMeshComponent>();
		auto tmpMI = MeshComponent->GetMaterial(0);
		if (tmpMI != MI_Preview_False)
			MI_Destroy = tmpMI;
		MeshComponent->SetMaterial(0, MI_Preview_False);
	}
	else
	{
		if (DestroyActor->IsValidLowLevel())
		{
			UStaticMeshComponent* MeshComponent = DestroyActor->FindComponentByClass<UStaticMeshComponent>();
			if (MeshComponent)
			{
				MeshComponent->SetMaterial(0, MI_Destroy);
			}
		}
		DestroyActor = nullptr;
	}
}

void UH_BuildComponent::F_EndDestroy()
{
	if (DestroyActor->IsValidLowLevel())
	{
		DestroyActor->Destroy();
		DestroyActor = nullptr;
	}
}
