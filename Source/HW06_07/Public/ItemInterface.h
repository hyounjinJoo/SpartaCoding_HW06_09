#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class HW06_07_API IItemInterface
{
	GENERATED_BODY()

public:
	virtual void OnItemBeginOverlap(AActor* OverlapActor) = 0;
	virtual void OnItemEndOverlap(AActor* OverlapActor) = 0;
	// 아이템 사용 시 호출
	virtual void ActivateItem(AActor* Activator) = 0;
	// "Coin", "Mine" 등 아이템 유형 반환
	virtual FName GetItemType() const = 0;
};