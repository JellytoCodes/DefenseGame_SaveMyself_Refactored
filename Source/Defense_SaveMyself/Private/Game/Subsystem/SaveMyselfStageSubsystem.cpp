
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"

void USaveMyselfStageSubsystem::BuildCache(const USaveMyselfStageInfo* StageAsset)
{
	if (IsValid(StageAsset))
	{
		CurrentStageInfo.PrepareTime = StageAsset->PrepareTime;
		CurrentStageInfo.ActionTime = StageAsset->ActionTime;
		CurrentStageInfo.CurrentStage = StageAsset->CurStage;
		CurrentStageInfo.NextStage = StageAsset->NextStage;
		CurrentStageInfo.CurrentStageQuestInfo = StageAsset->CurrentStageQuestInfo;
		CurrentStageInfo.CurStageText = StageAsset->CurStageText;
	}
}

USaveMyselfStageSubsystem* USaveMyselfStageSubsystem::GetStageSubsystem(const UObject* WorldContext)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull))
	{
		return World->GetSubsystem<USaveMyselfStageSubsystem>();
	}
	return nullptr;	
}

void USaveMyselfStageSubsystem::PreparePhaseCountdown()
{
	Timer = CurrentStageInfo.PrepareTime;
	GetWorld()->GetTimerManager().SetTimer(CountdownHandle, this, &USaveMyselfStageSubsystem::TimerCountdown, 1.f, true);
}

void USaveMyselfStageSubsystem::TimerCountdown()
{
	if (--Timer < 0)
	{
		ClearCountdown();
		if (bPreparePhase)
		{
			bPreparePhase = false;
			bActionPhase = true;
			ActionPhaseCountdown();
		}

		else if (bActionPhase)
		{
			OnTimeOutDelegate.Broadcast();
		}
	}
	else
	{
		if (bPreparePhase)	OnPrepareTimerHandleDelegate.Broadcast(Timer);
		if (bActionPhase)	OnActionTimerHandleDelegate.Broadcast(Timer);
	}
}

void USaveMyselfStageSubsystem::ActionPhaseCountdown()
{
	Timer = CurrentStageInfo.ActionTime;

	OnActionPhaseDelegate.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(CountdownHandle, this, &USaveMyselfStageSubsystem::TimerCountdown, 1.f, true);
}

void USaveMyselfStageSubsystem::ClearCountdown()
{
	GetWorld()->GetTimerManager().ClearTimer(CountdownHandle);
}

FText USaveMyselfStageSubsystem::GetStageNum() const
{
	return CurrentStageInfo.CurStageText;
}

FText USaveMyselfStageSubsystem::GetQuestDescription() const
{
	return CurrentStageInfo.CurrentStageQuestInfo.StageQuestDescription;
}

bool USaveMyselfStageSubsystem::GetPreparePhase() const
{
	return bPreparePhase;
}

EStageQuestType USaveMyselfStageSubsystem::GetStageQuestType() const
{
	return CurrentStageInfo.CurrentStageQuestInfo.QuestType;
}

FName USaveMyselfStageSubsystem::GetNextStage() const
{
	return CurrentStageInfo.NextStage;
}

FStageQuestInfo USaveMyselfStageSubsystem::GetStageQuestInfo() const
{
	return CurrentStageInfo.CurrentStageQuestInfo;
}

void USaveMyselfStageSubsystem::EnemyKilledCount()
{
	if (++KilledCount == CurrentStageInfo.CurrentStageQuestInfo.KilledEnemies)
	{
		OnEnemyKilledDelegate.Broadcast();
	}
	OnEnemyKilledCountDelegate.Broadcast(KilledCount);
}
