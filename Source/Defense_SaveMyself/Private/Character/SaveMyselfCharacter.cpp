#include "Character/SaveMyselfCharacter.h"
#include "Camera/CameraActor.h"
#include "Components/ActorSpawnComponent.h"
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SaveMyselfPlayerController.h"
#include "UI/HUD/SaveMyselfHUD.h"
#include "UI/WidgetComponents/ConfirmPlacedWidgetComponent.h"


ASaveMyselfCharacter::ASaveMyselfCharacter()
{
	ActorSpawnComponent = CreateDefaultSubobject<UActorSpawnComponent>("ActorSpawnComponent");
}

void ASaveMyselfCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeCharacterInfo();
}

void ASaveMyselfCharacter::InitializeCharacterInfo()
{
	if (const ASaveMyselfPlayerController* SaveMyselfPlayerController = Cast<ASaveMyselfPlayerController>(GetController()))
	{
		if (ASaveMyselfHUD* SaveMyselfHUD = Cast<ASaveMyselfHUD>(SaveMyselfPlayerController->GetHUD()))
		{
			SaveMyselfHUD->InitPlayerQuickSlot();
			SaveMyselfHUD->InitStageInfoWidget();
			SaveMyselfHUD->InitPauseMenu();
		}
	}

	if (ConfirmPlacedWidgetComponentClass)
	{
		ConfirmPlacedWidgetComponent = NewObject<UConfirmPlacedWidgetComponent>(this, ConfirmPlacedWidgetComponentClass);
		ConfirmPlacedWidgetComponent->RegisterComponent();
		ConfirmPlacedWidgetComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		ConfirmPlacedWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	}

	if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
	{
		if (StageSubsystem->GetStageQuestType() == EStageQuestType::TimeLimit)
		{
			StageSubsystem->OnTimeOutDelegate.AddUObject(this, &ASaveMyselfCharacter::OnStageVictoryBroadcast);
		}
		else if (StageSubsystem->GetStageQuestType() == EStageQuestType::EnemyAllKill)
		{
			StageSubsystem->OnEnemyKilledDelegate.AddUObject(this, &ASaveMyselfCharacter::OnStageDefeatBroadcast);
			StageSubsystem->OnEnemyKilledDelegate.AddUObject(this, &ASaveMyselfCharacter::OnStageVictoryBroadcast);
		}
		else if (StageSubsystem->GetStageQuestType() == EStageQuestType::TargetDestroy)
		{
			StageSubsystem->OnTimeOutDelegate.AddUObject(this, &ASaveMyselfCharacter::OnStageDefeatBroadcast);
			StageSubsystem->OnEnemyKilledDelegate.AddUObject(this, &ASaveMyselfCharacter::OnStageVictoryBroadcast);
		}
	}

	FActorSpawnParameters SpawnParams;
	WinCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), SpawnParams);
	DefeatCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), SpawnParams);
}

void ASaveMyselfCharacter::OnStageDefeatBroadcast() const
{
	if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
	{
		StageSubsystem->ClearCountdown();
		OnStageDefeatDelegate.Broadcast();
		SetViewDefeatCamera();
	}
	HideHUD();
}

void ASaveMyselfCharacter::OnStageVictoryBroadcast() const
{
	if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
	{
		StageSubsystem->ClearCountdown();
		OnStageVictoryDelegate.Broadcast();
		SetViewWinCamera();
	}
	HideHUD();
}

void ASaveMyselfCharacter::SetViewWinCamera() const
{
	const FVector CharLoc = this->GetActorLocation();

	const FVector CamLoc = CharLoc + this->GetActorForwardVector() * 400.f + FVector(0.f, 50.f, 120.f);
	const FRotator CamRot = (CharLoc - CamLoc).Rotation();

	if(!WinCamera) return;
	
	WinCamera->SetActorLocation(CamLoc);
	WinCamera->SetActorRotation(CamRot);
	
	if(const auto PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		PC->SetViewTargetWithBlend(WinCamera, .1f, EViewTargetBlendFunction::VTBlend_EaseInOut, 0.f, false);
	}
}

void ASaveMyselfCharacter::SetViewDefeatCamera() const
{
	const FVector StartLoc = this->GetActorLocation() + FVector(0.f, 0.f, 150.f);
	const FVector EndLoc = StartLoc + FVector(0.f, 0.f, 400.f);
	const FRotator CamRot = FRotator(-90.f, 0.f, 0.f);

	if(!DefeatCamera) return;
	
	DefeatCamera->SetActorLocation(EndLoc);
	DefeatCamera->SetActorRotation(CamRot);

	if(const auto PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		PC->SetViewTargetWithBlend(DefeatCamera, .1f, EViewTargetBlendFunction::VTBlend_EaseInOut, 0.f, false);
	}
	
}

void ASaveMyselfCharacter::HideHUD() const
{
	if (const ASaveMyselfPlayerController* SaveMyselfPlayerController = Cast<ASaveMyselfPlayerController>(GetController()))
	{
		if (const ASaveMyselfHUD* SaveMyselfHUD = Cast<ASaveMyselfHUD>(SaveMyselfPlayerController->GetHUD()))
		{
			SaveMyselfHUD->HidePlayerQuickSlot();
			SaveMyselfHUD->HideStageInfoWidget();
		}
	}
}

void ASaveMyselfCharacter::DamagedEvent_Implementation(const float Damage)
{
	if (--PlayerHP <= 0)
	{
		OnStageDefeatBroadcast();
	}
	PlayerLifeDelegate.Broadcast(PlayerHP);
}
