#include "Character/SaveMyselfCharacter.h"

#include "Components/ActorSpawnComponent.h"
#include "Player/SaveMyselfPlayerController.h"
#include "UI/HUD/SaveMyselfHUD.h"

ASaveMyselfCharacter::ASaveMyselfCharacter()
{
	ActorSpawnComponent = CreateDefaultSubobject<UActorSpawnComponent>(TEXT("ActorSpawnComponent"));
}

void ASaveMyselfCharacter::DamagedEvent_Implementation(const float Damage)
{
	if (--PlayerHP <= 0)
	{
		OnStageDefeatDelegate.Broadcast();
	}
	PlayerLifeDelegate.Broadcast(PlayerHP);
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
			SaveMyselfHUD->InitStageInfoWidget();
		}
	}
}
