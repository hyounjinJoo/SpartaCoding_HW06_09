// Fill out your copyright notice in the Description page of Project Settings.


#include "CuttedDoughnutPlatform.h"

#include "LandscapeGizmoActiveActor.h"
#include "ProceduralMeshComponent.h"

ACuttedDoughnutPlatform::ACuttedDoughnutPlatform()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACuttedDoughnutPlatform::BeginPlay()
{
	Super::BeginPlay();
	ActivatePlatform(nullptr);
}

void ACuttedDoughnutPlatform::ActivatePlatform(AActor* InActivator)
{
	Super::ActivatePlatform(InActivator);

	FTimerManager& TimerManager = GetWorldTimerManager();
	TimerManager.SetTimer(TimerHandle, this, &ACuttedDoughnutPlatform::Act,
		TimerInterval, bTimerRepeat, TimerDuration);

	RotationScale *= (FMath::RandBool() ? -1.f : 1.f);
}

void ACuttedDoughnutPlatform::Act()
{
	Super::Act();

	checkf(Root, TEXT("Root is null"));
	checkf(Root.Get(), TEXT("Root is null"));
	if(!IsValid(Root.Get()))
	{
		return;
	}
	
	static float RotationDelta = 0.f;
	RotationDelta = FMath::DegreesToRadians(RotationSpeed * RotationScale);
	
	FQuat NextQuat = GetActorRotation().Quaternion();
	switch(RotationDir)
	{
	case EDoughnutRotationDIR::X:
		NextQuat *= FQuat(FVector::ForwardVector, RotationDelta);
		break;
	case EDoughnutRotationDIR::Y:
		NextQuat *= FQuat(FVector::RightVector, RotationDelta);
		break;
	case EDoughnutRotationDIR::Z:
		NextQuat *= FQuat(FVector::UpVector, RotationDelta);
		break;
	default:
		checkNoEntry();
		break;
	}

	SetActorRotation(NextQuat);
}