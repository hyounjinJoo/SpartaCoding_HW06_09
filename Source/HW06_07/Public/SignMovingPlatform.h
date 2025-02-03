
#pragma once

#include "CoreMinimal.h"
#include "BasePlatform.h"
#include "SignMovingPlatform.generated.h"

UCLASS()
class HW06_07_API ASignMovingPlatform final : public ABasePlatform 
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform | Movement | Location")
	FVector StartPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform | Movement | Location", meta = (MakeEditWidget = "true"))
	FVector EditableTargetPosition;
	FVector ActualTargetPosition;
	UPROPERTY(EditAnywhere, Category = "Platform | Movement")
	float MovingSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category = "Platform | Movement")
	float MovingScale = 1.f;
	UPROPERTY(VisibleAnywhere, Category = "Platform | Movement")
	float MovingDeterminant = 0.f;
	
public:
	ASignMovingPlatform();

protected:
	virtual void BeginPlay() final;
	
private:
	virtual void ActivatePlatform(AActor* InActivator) final;
	virtual void Act() final;

private:
	void SetDefaultLocationsValue();
};