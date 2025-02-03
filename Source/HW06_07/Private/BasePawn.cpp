#include "BasePawn.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

