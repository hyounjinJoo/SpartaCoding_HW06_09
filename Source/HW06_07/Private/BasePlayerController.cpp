#include "BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "HWGameStateBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "BaseGameInstance.h"
#include "Components/Button.h"

ABasePlayerController::ABasePlayerController()
{
}

UUserWidget* ABasePlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void ABasePlayerController::ShowGameHUD()
{
	// HUD가 켜져 있다면 닫기
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance->MarkAsGarbage();
		HUDWidgetInstance = nullptr;
	}
	
	// 이미 메뉴가 떠 있으면 제거
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance->MarkAsGarbage();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
			
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());

			AHWGameStateBase* HWGameState = GetWorld() ? GetWorld()->GetGameState<AHWGameStateBase>() : nullptr;
			if(HWGameState)
			{
				HWGameState->UpdateHUD();
			}
		}
	}
}

void ABasePlayerController::ShowMainMenu(bool bIsRestart, bool bIsGameOver)
{
	// HUD가 켜져 있다면 닫기
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance->MarkAsGarbage();
		HUDWidgetInstance = nullptr;
	}
	
	// 이미 메뉴가 떠 있으면 제거
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance->MarkAsGarbage();
		MainMenuWidgetInstance = nullptr;
	}
	
	// 메뉴 UI 생성
	if (MainMenuWidgetClass)
	{		
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
			
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}
		
		UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText")));
		if (ButtonText)
		{
			if (bIsRestart || !bIsGameOver)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}

		ESlateVisibility Visibility = !bIsGameOver ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
		UButton* Button = Cast<UButton>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("ExitButton")));
		if(Button)
		{
			Button->SetVisibility(Visibility);
		}
		ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("ExitButtonText")));
		if(ButtonText)
		{
			ButtonText->SetVisibility(Visibility);
		}
	}
}

void ABasePlayerController::StartGame()
{	
	
	UGameplayStatics::OpenLevel(GetWorld(), FName("LV_HW08_Play"));
	
	{
		AHWGameStateBase* HWGameState = Cast<AHWGameStateBase>(UGameplayStatics::GetGameState(this));
		{
			HWGameState->CurrentLevelIndex = 0;
			HWGameState->Score = 0;
		}

		if(UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this)))
		{
			GameInstance->CurrentWaveIndex = 0;
			GameInstance->TotalScore = 0;
		}
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(TObjectPtr<ULocalPlayer> LocalPlayer = GetLocalPlayer())
	{
		if(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if(InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	// 게임 실행 시 메뉴 레벨에서 메뉴 UI 먼저 표시
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MainMenu"))
	{
		ShowMainMenu(false, true);
	}

	AHWGameStateBase* HWGameState = GetWorld() ? GetWorld()->GetGameState<AHWGameStateBase>() : nullptr;;
	if (HWGameState)
	{
		HWGameState->UpdateHUD();
	}
}