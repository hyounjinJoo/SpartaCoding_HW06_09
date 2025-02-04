// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlatformInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
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