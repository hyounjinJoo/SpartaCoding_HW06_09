
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlatformInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPlatformInterface : public UInterface
{
	GENERATED_BODY()
};

class HW06_07_API IPlatformInterface
{
	GENERATED_BODY()

public:
	virtual void ActivatePlatform(AActor* InActivator) = 0;
	virtual void Act() = 0;
};