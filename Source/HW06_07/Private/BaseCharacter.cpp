#include "BaseCharacter.h"

#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	// 카메라는 스프링 암의 회전을 따르므로 PawnControlRotation 비활성화
	Camera->bUsePawnControlRotation = false;

	DefaultWalkSpeed = 600.f;
	SprintSpeedMultiplier = 1.5f;
	SprintSpeed = DefaultWalkSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindActions(PlayerInputComponent);

}

bool ABaseCharacter::BindActions(UInputComponent* PlayerInputComponent)
{
	ensureMsgf(PlayerInputComponent, TEXT("Player Input Component is NULL, check Component"));
	
	bool bSuccess = true;
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
					&ABaseCharacter::Move);
			}
			else bSuccess = false;
			if(PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ABaseCharacter::Look);
			}
			else bSuccess = false;
			if(PlayerController->BoostAction)
			{
				EnhancedInput->BindAction(
					PlayerController->BoostAction,
					ETriggerEvent::Triggered,
					this,
					&ABaseCharacter::StartBoost);
				
				EnhancedInput->BindAction(
					PlayerController->BoostAction,
					ETriggerEvent::Completed,
					this,
					&ABaseCharacter::StopBoost);				
			}
			else bSuccess = false;
			if(PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ABaseCharacter::StartJump);
				
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ABaseCharacter::StopJump);				
			}
			else bSuccess = false;			
		}
		else
		{
			bSuccess = false;
		}
	}
	else
	{
		bSuccess = false;
	}

	return bSuccess;
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	if(!Controller) return;

	const FVector2D MoveInput = Value.Get<FVector2D>();

	if(!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if(!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}	
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	if(!Controller) return;

	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}
void ABaseCharacter::StartBoost(const FInputActionValue& Value)
{
	if(!Controller) return;

	if(GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}	
}
void ABaseCharacter::StopBoost(const FInputActionValue& Value)
{
	if(!Controller) return;
	
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}
}
void ABaseCharacter::StartJump(const FInputActionValue& Value)
{
	if(!Controller) return;

	if(Value.Get<bool>())
	{
		Jump();
	}	
}
void ABaseCharacter::StopJump(const FInputActionValue& Value)
{
	if(!Controller) return;

	if(!Value.Get<bool>())
	{
		StopJumping();
	}
}
