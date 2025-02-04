#include "CharacterPawn.h"

#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"


ACharacterPawn::ACharacterPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	BodyComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Body Component");
	BodyComponent->SetupAttachment(GetRootComponent());

}

void ACharacterPawn::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(BodyComponent.Get(), TEXT("Select Body"));
	CurrentWalkSpeed = WalkSpeed;
	
}

void ACharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(TObjectPtr<UEnhancedInputComponent> EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(TObjectPtr<ABasePlayerController> PlayerController = Cast<ABasePlayerController>(GetController()))
		{
			if(PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ACharacterPawn::Move);
			}
			if(PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ACharacterPawn::Look);
			}
			if(PlayerController->BoostAction)
			{
				// IA_Jump 액션 키를 누르고 있는 동안.
				EnhancedInput->BindAction(
					PlayerController->BoostAction,
					ETriggerEvent::Triggered,
					this,
					&ACharacterPawn::StartBoost);
				// IA_Jump 액션 키에서 손을 뗀 순간 호출
				EnhancedInput->BindAction(
					PlayerController->BoostAction,
					ETriggerEvent::Completed,
					this,
					&ACharacterPawn::StopBoost);
			}
		}
	}
}

void ACharacterPawn::Move(const FInputActionValue& Value)
{
	if(!Controller) return;

	const FVector2D MoveInput = Value.Get<FVector2D>();

	const float Move = GetWorld()->GetDeltaSeconds() * CurrentWalkSpeed;

	FVector DeltaLocation = FVector::ZeroVector;
	
	if(!FMath::IsNearlyZero(MoveInput.X))
	{
		float MoveX = Move * MoveInput.X;
		if(FMath::Abs(MoveX) > MaxWalkSpeed)
		{
			MoveX = MaxWalkSpeed;
		}
		
		DeltaLocation += GetActorForwardVector() * MoveX;
		
	}
	
	if(!FMath::IsNearlyZero(MoveInput.Y))
	{
		float MoveY = Move * MoveInput.Y;
		if(FMath::Abs(MoveY) > MaxWalkSpeed)
		{
			MoveY = MaxWalkSpeed;
		}
		
		DeltaLocation += GetActorRightVector() * MoveY;
	}

	AddActorWorldOffset(DeltaLocation, true);
}

void ACharacterPawn::Look(const FInputActionValue& Value)
{
	if(!Controller) return;

	const FVector2D LookInput = Value.Get<FVector2D>();

	const float Look = GetWorld()->GetDeltaSeconds() * LookSpeed;

	FQuat DeltaQuat = FQuat::Identity;
	
	if(!FMath::IsNearlyZero(LookInput.X))
	{
		float LookX = Look * LookInput.X;
		if(FMath::Abs(LookX) > MaxLookSpeed)
		{
			LookX = MaxLookSpeed;
		}
		
		DeltaQuat.Z += LookX;

		AddActorWorldRotation(DeltaQuat);
	}
	
	if(!FMath::IsNearlyZero(LookInput.Y))
	{
		float LookY = Look * LookInput.Y;
		if(FMath::Abs(LookY) > MaxLookSpeed)
		{
			LookY = MaxLookSpeed;
		}
		
		DeltaQuat.Y += LookY;
		DeltaQuat.Z = 0;
		SpringArm->AddLocalRotation(DeltaQuat);
	}	
}

void ACharacterPawn::StartBoost(const FInputActionValue& Value)
{
	CurrentWalkSpeed = BoostSpeed;
}

void ACharacterPawn::StopBoost(const FInputActionValue& Value)
{
	CurrentWalkSpeed = WalkSpeed;
}

