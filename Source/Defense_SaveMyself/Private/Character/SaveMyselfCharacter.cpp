#include "Character/SaveMyselfCharacter.h"

#include "Components/ActorSpawnComponent.h"
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"
#include "Player/SaveMyselfPlayerController.h"
#include "UI/HUD/SaveMyselfHUD.h"
#include "UI/WidgetComponents/ConfirmPlacedWidget.h"


ASaveMyselfCharacter::ASaveMyselfCharacter()
{
	ActorSpawnComponent = CreateDefaultSubobject<UActorSpawnComponent>("ActorSpawnComponent");
}

void ASaveMyselfCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeCharacterInfo();

	if (ConfirmPlacedWidgetComponentClass)
	{
		ConfirmPlacedWidgetComponent = NewObject<UConfirmPlacedWidget>(this, ConfirmPlacedWidgetComponentClass);
		ConfirmPlacedWidgetComponent->RegisterComponent();
		ConfirmPlacedWidgetComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		ConfirmPlacedWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	}

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
		else if (StageSubsystem->GetStageQuestType() == EStageQuestType::TargetDestroy)
		{
			StageSubsystem->OnTimeOutDelegate.AddUObject(this, &ASaveMyselfCharacter::OnStageDefeatBroadCast);
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
	if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
	{
		StageSubsystem->ClearCountdown();
		OnStageDefeatDelegate.Broadcast();
	}
}

void ASaveMyselfCharacter::OnStageVictoryBroadCast() const
{
	if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
	{
		StageSubsystem->ClearCountdown();
		OnStageVictoryDelegate.Broadcast();
	}
}

void ASaveMyselfCharacter::DamagedEvent_Implementation(const float Damage)
{
	if (--PlayerHP <= 0)
	{
		OnStageDefeatBroadCast();
	}
	PlayerLifeDelegate.Broadcast(PlayerHP);
}