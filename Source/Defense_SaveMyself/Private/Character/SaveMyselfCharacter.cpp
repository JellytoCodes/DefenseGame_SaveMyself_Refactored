#include "Character/SaveMyselfCharacter.h"

#include "Components/ActorSpawnComponent.h"
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"
#include "Player/SaveMyselfPlayerController.h"
#include "UI/HUD/SaveMyselfHUD.h"


ASaveMyselfCharacter::ASaveMyselfCharacter()
{
	ActorSpawnComponent = CreateDefaultSubobject<UActorSpawnComponent>(TEXT("ActorSpawnComponent"));
}

void ASaveMyselfCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeCharacterInfo();


	if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
	{
		if (StageSubsystem->GetStageQuestType() == EStageQuestType::TimeLimit)
		{
			StageSubsystem->OnTimeOutDelegate.AddUObject(this, &ASaveMyselfCharacter::OnStageVictoryBroadCast);
		}
		else if (StageSubsystem->GetStageQuestType() == EStageQuestType::EnemyAllKill)
		{
			StageSubsystem->OnEnemyKilledDelegate.AddUObject(this, &ASaveMyselfCharacter::OnStageDefeatBroadCast);
			StageSubsystem->OnEnemyKilledDelegate.AddUObject(this, &ASaveMyselfCharacter::OnStageVictoryBroadCast);
		}
	}
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

void ASaveMyselfCharacter::OnStageDefeatBroadCast() const
{
	OnStageDefeatDelegate.Broadcast();
}

void ASaveMyselfCharacter::OnStageVictoryBroadCast() const
{
	OnStageVictoryDelegate.Broadcast();
}

void ASaveMyselfCharacter::DamagedEvent_Implementation(const float Damage)
{
	if (--PlayerHP <= 0)
	{
		OnStageDefeatBroadCast();
	}
	PlayerLifeDelegate.Broadcast(PlayerHP);
}