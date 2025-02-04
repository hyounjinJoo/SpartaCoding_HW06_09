#pragma once

#include "CoreMinimal.h"
#include "PlatformInterface.h"
#include "GameFramework/Actor.h"
#include "BasePlatform.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class HW06_07_API ABasePlatform : public AActor, public IPlatformInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(BlueprintReadOnly, Category = "Platform | Timer")
	FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere, Category = "Platform | Timer")
	float TimerInterval = 0.1f;
	UPROPERTY(EditAnywhere, Category = "Platform | Timer")
	bool bTimerRepeat = true;
	UPROPERTY(EditAnywhere, Category = "Platform | Timer")
	float TimerDuration = 0.f;	
	
public:
	ABasePlatform();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Destroyed() override;

protected:
	virtual void TimerPause() final;
	virtual void TimerResume() final;

protected:
	virtual void ActivatePlatform(AActor* InActivator) override;
	virtual void Act() override;
};