// Fill out your copyright notice in the Description page of Project Settings.


#include "LHJ/H_BuildComponent.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "PlumDefense.h"

#include "Camera/CameraComponent.h"
#include "LHJ/H_User.h"

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
}


// Called when the game starts
void UH_BuildComponent::BeginPlay()
{
	Super::BeginPlay();

	UserCamera = user->GetComponentByClass<UCameraComponent>();

	PreviewMesh = Cast<UStaticMeshComponent>
	(user->AddComponentByClass(UStaticMeshComponent::StaticClass(), false,
	                           FTransform::Identity, false));

	// Static Mesh 설정
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(
		nullptr, TEXT("/Script/Engine.StaticMesh'/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01'"));
	if (Mesh)
	{
		PreviewMesh->SetStaticMesh(Mesh);
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
		PreviewMesh->SetWorldTransform(BuildTransform);
		PreviewMesh->SetMaterial(0, MI_Preview_True);
		bCanPlace = true;
		LOG_S(Warning, TEXT("Hit: %s"), *outHit.GetActor()->GetName());
	}
	else
	{
		PreviewMesh->SetWorldTransform(FTransform(end));
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
	GetWorld()->SpawnActor<AActor>(PlaceTower, BuildTransform, SpawnParams);
}
