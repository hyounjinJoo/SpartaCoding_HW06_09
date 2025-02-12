#include "SmallCoinItem.h"


ASmallCoinItem::ASmallCoinItem()
{
	PrimaryActorTick.bCanEverTick = false;

	PointValue = 10;
	ItemType = "SmallCoin";
}

void ASmallCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}