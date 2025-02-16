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

	MaxHealth = 100.f;
	Health = MaxHealth;
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

void ABaseCharacter::AddHealth(float Amount)
{
	// 체력을 회복시킴. 최대 체력을 초과하지 않도록 제한함
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Health increased to: %f"), Health));
}

void ABaseCharacter::OnDeath()
{
    UE_LOG(LogTemp, Error, TEXT("Character is Dead!"));
}

float ABaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	// 기본 데미지 처리 로직 호출 (필수는 아님)
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 체력을 데미지만큼 감소시키고, 0 이하로 떨어지지 않도록 Clamp
	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health decreased to: %f"), Health));

	// 체력이 0 이하가 되면 사망 처리
	if (Health <= 0.0f)
	{
		OnDeath();
	}

	// 실제 적용된 데미지를 반환
	return ActualDamage;
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
			if(PlayerController->OpenMainMenuAction)
			{
				EnhancedInput->BindAction(
					PlayerController->OpenMainMenuAction,
					ETriggerEvent::Completed,
					this,
					&ABaseCharacter::OpenMenu);
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

void ABaseCharacter::OpenMenu(const FInputActionValue& Value)
{
	if(TObjectPtr<UEnhancedInputComponent> EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if(TObjectPtr<ABasePlayerController> PlayerController = Cast<ABasePlayerController>(GetController()))
		{
			FString CurrentMapName = GetWorld()->GetMapName();
			if (CurrentMapName.Contains("Play"))
			{				
				PlayerController->Pause();
				PlayerController->ShowMainMenu(true, false);
			}
		}
	}
}