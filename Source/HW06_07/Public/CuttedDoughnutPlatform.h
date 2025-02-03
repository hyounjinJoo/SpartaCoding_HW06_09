#pragma once

#include "CoreMinimal.h"
#include "BasePlatform.h"
#include "CuttedDoughnutPlatform.generated.h"

UENUM()
enum class EDoughnutRotationDIR : uint8
{
	X = 0	UMETA(DisplayName = "X"),
	Y		UMETA(DisplayName = "Y"),
	Z		UMETA(DisplayName = "Z"),
};

UCLASS()
class HW06_07_API ACuttedDoughnutPlatform final : public ABasePlatform
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Platform | Movement")
	float RotationSpeed = 100.f;
	UPROPERTY(EditAnywhere, Category = "Platform | Movement")
	float RotationScale = 1.f;
	UPROPERTY(EditAnywhere, Category = "Platform | Movement")
	EDoughnutRotationDIR RotationDir = EDoughnutRotationDIR::Z;
	
public:
	ACuttedDoughnutPlatform();

protected:
	virtual void BeginPlay() final;

private:
	virtual void ActivatePlatform(AActor* InActivator) final;
	virtual void Act() final;
};