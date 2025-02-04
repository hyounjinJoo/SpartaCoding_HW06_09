#include "CharacterPawn.h"

#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"



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
			if(PlayerController->JumpAction)
			{
				// IA_Jump 액션 키를 누르고 있는 동안.
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ACharacterPawn::StartJump);
				// IA_Jump 액션 키에서 손을 뗀 순간 호출
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ACharacterPawn::StopJump);
			}
			if(PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ACharacterPawn::Look);
			}
			if(PlayerController->SprintAction)
			{
				// IA_Jump 액션 키를 누르고 있는 동안.
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ACharacterPawn::StartSprint);
				// IA_Jump 액션 키에서 손을 뗀 순간 호출
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ACharacterPawn::StopSprint);
			}
		}
	}
}

void ACharacterPawn::Move(const FInputActionValue& Value)
{
	if(!Controller) return;

	const FVector2D MoveInput = Value.Get<FVector2D>();

	const float Move = GetWorld()->GetDeltaSeconds() * WalkSpeed;

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

	AddActorWorldOffset(DeltaLocation);
}

void ACharacterPawn::StartJump(const FInputActionValue& Value)
{
}

void ACharacterPawn::StopJump(const FInputActionValue& Value)
{
}

void ACharacterPawn::Look(const FInputActionValue& Value)
{
}

void ACharacterPawn::StartSprint(const FInputActionValue& Value)
{
}

void ACharacterPawn::StopSprint(const FInputActionValue& Value)
{
}

