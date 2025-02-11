#include "BaseGameMode.h"

#include "BasePlayerController.h"

ABaseGameMode::ABaseGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Blueprint/Character/BP_CharacterPawn"));
	if(PlayerPawn.Class)
	{
		DefaultPawnClass = PlayerPawn.Class;
	}
	
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Game/Blueprint/Input/Controller/BP_PlayerController"));
	if(PlayerController.Class)
	{
		PlayerControllerClass = PlayerController.Class;		
	}
}