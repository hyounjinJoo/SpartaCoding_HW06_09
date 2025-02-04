// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "CharacterPawn.generated.h"

class USkeletalMeshComponent;
struct FInputActionValue;

UCLASS()
class HW06_07_API ACharacterPawn : public ABasePawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character | Body")
	TObjectPtr<USkeletalMeshComponent> BodyComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Movement")
	float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Movement")
	float BoostSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Movement")
	float MaxWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Movement")
	float LookSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Movement")
	float MaxLookSpeed;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Movement", meta = (AllowPrivateAccess = "true"))
	float CurrentWalkSpeed;
	
public:
	// Sets default values for this pawn's properties
	ACharacterPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region InputFunctions
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void StartBoost(const FInputActionValue& Value);
	UFUNCTION()
	void StopBoost(const FInputActionValue& Value);
#pragma endregion InputFunctions
};