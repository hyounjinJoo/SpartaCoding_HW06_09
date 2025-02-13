// Fill out your copyright notice in the Description page of Project Settings.


#include "HWGameStateBase.h"

#include "BasePlayerController.h"
#include "CoinItem.h"
#include "SpawnVolume.h"
#include "Kismet/GameplayStatics.h"

AHWGameStateBase::AHWGameStateBase()
{
    Score = 0;
    
    SpawnedCoinCount = 0;
    CollectedCoinCount = 0;
    LevelDuration = 30.0f; // 한 레벨당 30초
    CurrentLevelIndex = 0;
    MaxLevels = 3;
}

void AHWGameStateBase::BeginPlay()
{
    Super::BeginPlay();

    StartLevel();
}

int32 AHWGameStateBase::GetScore() const
{
    return Score;
}

int32 AHWGameStateBase::GetLevelNumber() const
{
    return CurrentLevelIndex + 1;
}

float AHWGameStateBase::GetRemainingTime()
{
    float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);

    return RemainingTime;
}

void AHWGameStateBase::AddScore(int32 Amount)
{
    Score += Amount;
}

void AHWGameStateBase::OnGameOver()
{
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (ABasePlayerController* SpartaPlayerController = Cast<ABasePlayerController>(PlayerController))
        {
            SpartaPlayerController->ShowMainMenu(true);
        }
    }
}

void AHWGameStateBase::StartLevel()
{
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (ABasePlayerController* SpartaPlayerController = Cast<ABasePlayerController>(PlayerController))
        {
            SpartaPlayerController->ShowGameHUD();
        }
    }
    
    // 레벨 시작 시, 코인 개수 초기화
    SpawnedCoinCount = 0;
    CollectedCoinCount = 0;
	
    // 현재 맵에 배치된 모든 SpawnVolume을 찾아 아이템 40개를 스폰
    TArray<AActor*> FoundVolumes;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	
    const int32 ItemToSpawn = 40;
    
    for (int32 i = 0; i < ItemToSpawn; i++)
    {
        if (FoundVolumes.Num() > 0)
        {    
            ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
            if (SpawnVolume)
            {                
                SpawnVolume->SetItemDataTable(LevelData[CurrentLevelIndex].Get());
                AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
                // 만약 스폰된 액터가 코인 타입이라면 SpawnedCoinCount 증가
                if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
                {
                    SpawnedCoinCount++;
                }
            }				
        }
    }
	
    // 30초 후에 OnLevelTimeUp()가 호출되도록 타이머 설정
    GetWorldTimerManager().SetTimer(
        LevelTimerHandle,
        this,
        &AHWGameStateBase::OnLevelTimeUp,
        LevelDuration,
        false
    );
	
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
    FString::Printf(TEXT("Wave %d을 시이이이이작 하겠읍니다~~~~~~~!!!!!!!!, Spawned %d coin"),
    CurrentLevelIndex + 1,
    SpawnedCoinCount));
}

void AHWGameStateBase::OnLevelTimeUp()
{
    // 시간이 다 되면 레벨을 종료
    EndLevel();
}

void AHWGameStateBase::OnCoinCollected()
{
    CollectedCoinCount++;
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,
        FString::Printf(TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount));
	
    // 현재 레벨에서 스폰된 코인을 전부 주웠다면 즉시 레벨 종료
    if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
    {
        EndLevel();
    }
}

void AHWGameStateBase::EndLevel()
{
    // 타이머 해제
    GetWorldTimerManager().ClearTimer(LevelTimerHandle);
    // 다음 레벨 인덱스로
    CurrentLevelIndex++;

    // 모든 레벨을 다 돌았다면 게임 오버 처리
    if (CurrentLevelIndex >= MaxLevels)
    {
        OnGameOver();
        return;
    }
		
    // 변경될 레벨 데이터가 있다면 레벨 시작
    if (LevelData.IsValidIndex(CurrentLevelIndex))
    {
        StartLevel();
    }
    else
    {
        // 없으면 게임오버
        OnGameOver();
    }
}