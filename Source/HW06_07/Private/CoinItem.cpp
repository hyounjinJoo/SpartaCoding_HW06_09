#include "CoinItem.h"

#include "HWGameStateBase.h"


ACoinItem::ACoinItem()
{
	PointValue = 0;
	ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	if(Activator && Activator->ActorHasTag("Player"))
	{
		if(UWorld* World = Activator->GetWorld())
		{
			if(AHWGameStateBase* GameState = World->GetGameState<AHWGameStateBase>())
			{
				GameState->AddScore(PointValue);
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green,
					FString::Printf(TEXT("Player Gained %d points! Current Point : %d"), PointValue, GameState->GetScore()));
				
				GameState->OnCoinCollected();
			}
		}

		DestroyItem();
	}
}

