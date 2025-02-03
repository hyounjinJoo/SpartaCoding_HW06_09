#include "SignMovingPlatform.h"

#include "Components/InterpToMovementComponent.h"


ASignMovingPlatform::ASignMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	if(IsValid(Mesh))
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
		if(CubeMesh.Succeeded())
		{
			Mesh->SetStaticMesh(CubeMesh.Object);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Load Cube mesh!"));
		}
	}
}

void ASignMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	SetDefaultLocationsValue();
	ActivatePlatform(nullptr);
}

void ASignMovingPlatform::ActivatePlatform(AActor* InActivator)
{
	Super::ActivatePlatform(InActivator);
	
	FTimerManager& TimerManager = GetWorldTimerManager();
	TimerManager.SetTimer(TimerHandle, this, &ASignMovingPlatform::Act,
		TimerInterval, bTimerRepeat, TimerDuration);
}

void ASignMovingPlatform::Act()
{
	Super::Act();

	MovingDeterminant += MovingSpeed * MovingScale * 0.001f;
	static float MovingAlpha = 0.f;
	MovingAlpha = (FMath::Sin(MovingDeterminant) + 1.f) * 0.5f;
	static FVector NextMovingLocation = FVector::Zero();
	NextMovingLocation = FMath::Lerp(StartPosition, ActualTargetPosition, MovingAlpha);

	EditableTargetPosition -= NextMovingLocation - GetActorLocation();
	SetActorLocation(NextMovingLocation);
}

void ASignMovingPlatform::SetDefaultLocationsValue()
{
	StartPosition = GetActorLocation();
	ActualTargetPosition = StartPosition + EditableTargetPosition;
}