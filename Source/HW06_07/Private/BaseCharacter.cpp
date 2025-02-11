#include "BaseCharacter.h"

#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
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
	
}
void ABaseCharacter::Look(const FInputActionValue& Value)
{
	if(!Controller) return;
	
}
void ABaseCharacter::StartBoost(const FInputActionValue& Value)
{
	if(!Controller) return;
	
}
void ABaseCharacter::StopBoost(const FInputActionValue& Value)
{
	if(!Controller) return;
	
}
void ABaseCharacter::StartJump(const FInputActionValue& Value)
{
	if(!Controller) return;
	
}
void ABaseCharacter::StopJump(const FInputActionValue& Value)
{
	if(!Controller) return;
	
}
