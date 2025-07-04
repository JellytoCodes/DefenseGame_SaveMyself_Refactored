#include "Character/SaveMyselfCharacter.h"

#include "Player/SaveMyselfPlayerController.h"
#include "UI/HUD/SaveMyselfHUD.h"

ASaveMyselfCharacter::ASaveMyselfCharacter()
{

}

void ASaveMyselfCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeCharacterInfo();
}

void ASaveMyselfCharacter::InitializeCharacterInfo()
{
	if (ASaveMyselfPlayerController* SaveMyselfPlayerController = Cast<ASaveMyselfPlayerController>(GetController()))
	{
		if (ASaveMyselfHUD* SaveMyselfHUD = Cast<ASaveMyselfHUD>(SaveMyselfPlayerController->GetHUD()))
		{
			SaveMyselfHUD->InitPlayerQuickSlot();
		}
	}
}
