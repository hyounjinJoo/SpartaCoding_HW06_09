// Fill out your copyright notice in the Description page of Project Settings.


#include "HWGameStateBase.h"

AHWGameStateBase::AHWGameStateBase()
{
		Score = 0;
}

int32 AHWGameStateBase::GetScore() const
{
    return Score;
}

void AHWGameStateBase::AddScore(int32 Amount)
{
    Score += Amount;
}