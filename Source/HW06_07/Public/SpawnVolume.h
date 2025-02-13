﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class HW06_07_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ASpawnVolume();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnRandomItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawning")
	USceneComponent* Scene;
	// 스폰 영역을 담당할 박스 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawning")
	UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	UDataTable* ItemDataTable;

	FVector GetRandomPointInVolume() const;
	FItemSpawnRow* GetRandomItem() const;
	void SpawnItem(TSubclassOf<AActor> ItemClass);
};