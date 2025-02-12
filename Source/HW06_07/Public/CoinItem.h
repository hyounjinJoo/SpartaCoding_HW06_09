#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "CoinItem.generated.h"

/*
 * Coin 아이템의 베이스 클래스.
 * Big / Small 코인 등의 하위 클래스의 부모가 된다.
 */
UCLASS()
class HW06_07_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ACoinItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue;

protected:
	virtual void ActivateItem(AActor* Activator) override;
};