// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UCLASS()
class HW06_07_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBaseGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentWaveIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
};
