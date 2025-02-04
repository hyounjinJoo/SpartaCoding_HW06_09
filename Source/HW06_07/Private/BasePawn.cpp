#include "BasePawn.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule Collision");
	SetRootComponent(Capsule);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Main Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>("Forward Arrow");
	ForwardArrow->SetupAttachment(GetRootComponent());
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

