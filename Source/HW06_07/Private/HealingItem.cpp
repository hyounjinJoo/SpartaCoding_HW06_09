// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"

#include "BaseCharacter.h"

AHealingItem::AHealingItem()
{
	HealAmount = 20.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(Activator))
	{
		Character->AddHealth(HealAmount);		        
		DestroyItem();
	}
}