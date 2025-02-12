// Fill out your copyright notice in the Description page of Project Settings.


#include "BigCoinItem.h"


// Sets default values
ABigCoinItem::ABigCoinItem()
{
	PrimaryActorTick.bCanEverTick = false;

	PointValue = 50;
	ItemType = "BigCoin";
}

void ABigCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}