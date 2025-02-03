#include "BasePlatform.h"

ABasePlatform::ABasePlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);
}

void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();	
}

void ABasePlatform::BeginDestroy()
{
	if(TimerHandle.IsValid() && GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		GetWorldTimerManager().ClearTimer(TimerHandle);
	
	Super::BeginDestroy();
}

void ABasePlatform::Destroyed()
{	
	Super::Destroyed();
}

void ABasePlatform::TimerPause()
{
	if(GetWorldTimerManager().IsTimerActive(TimerHandle))
		GetWorldTimerManager().PauseTimer(TimerHandle);
}

void ABasePlatform::TimerResume()
{
	if(GetWorldTimerManager().IsTimerPaused(TimerHandle))
		GetWorldTimerManager().UnPauseTimer(TimerHandle);
}

void ABasePlatform::ActivatePlatform(AActor* InActivator)
{
}

void ABasePlatform::Act()
{
}