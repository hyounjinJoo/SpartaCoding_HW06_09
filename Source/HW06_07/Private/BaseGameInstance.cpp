// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"

UBaseGameInstance::UBaseGameInstance()
{
	TotalScore = 0;
	CurrentWaveIndex = 0;
}

void UBaseGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
		FString::Printf(TEXT("Total Score Updated: %d"), TotalScore));
}