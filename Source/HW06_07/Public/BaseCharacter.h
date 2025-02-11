// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

struct FInputActionValue;
class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UInputComponent;

UCLASS()
class HW06_07_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	TObjectPtr<UCameraComponent> Camera;
	
public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void StartBoost(const FInputActionValue& Value);
	UFUNCTION()
	void StopBoost(const FInputActionValue& Value);
	UFUNCTION()
	void StartJump(const FInputActionValue& Value);
	UFUNCTION()
	void StopJump(const FInputActionValue& Value);

private:
	bool BindActions(UInputComponent* PlayerInputComponent);
};