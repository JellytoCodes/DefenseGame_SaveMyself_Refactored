#pragma once

#include "CoreMinimal.h"
#include "Data/SaveMyselfStageInfo.h"
#include "Subsystems/WorldSubsystem.h"
#include "SaveMyselfStageSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseTimerHandleSignature, int32, Timer);
DECLARE_MULTICAST_DELEGATE(FOnPhaseStateHandleSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKilledCounterDelegate, int32, KilledCount);
USTRUCT(BlueprintType)
struct FCurrentStageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PrepareTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ActionTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CurrentStage = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName NextStage = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FStageQuestInfo CurrentStageQuestInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CurStageText;
};

UCLASS()
class DEFENSE_SAVEMYSELF_API USaveMyselfStageSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public :
	void BuildCache(const USaveMyselfStageInfo* StageAsset);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContext"))
	static USaveMyselfStageSubsystem* GetStageSubsystem(const UObject* WorldContext);

	/** Delegate */
	FCurrentStageInfo CurrentStageInfo;
	FOnPhaseStateHandleSignature OnActionPhaseDelegate;
	FOnPhaseStateHandleSignature OnTimeOutDelegate;
	FOnPhaseStateHandleSignature OnEnemyKilledDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPhaseTimerHandleSignature OnPrepareTimerHandleDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPhaseTimerHandleSignature OnActionTimerHandleDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnKilledCounterDelegate OnEnemyKilledCountDelegate;

	/** end Delegate */

	UFUNCTION(BlueprintCallable, Category = "StageInfo|PreparePhase")
	void PreparePhaseCountdown();

	UFUNCTION(BlueprintCallable, Category = "StageInfo|ActionPhase")
	void ActionPhaseCountdown();

	UFUNCTION(BlueprintCallable, Category = "StageInfo|ClearTimer")
	void ClearCountdown();

	UFUNCTION(BlueprintPure, Category = "StageInfo")
	FText GetStageNum() const;

	UFUNCTION(BlueprintPure, Category = "StageInfo")
	FText GetQuestDescription() const;

	UFUNCTION(BlueprintPure, Category = "StageInfo")
	bool GetPreparePhase() const;

	UFUNCTION(BlueprintPure, Category = "StageInfo")
	EStageQuestType GetStageQuestType() const;

	UFUNCTION(BlueprintPure, Category = "StageInfo")
	FName GetNextStage() const;

	UFUNCTION(BlueprintPure, Category = "StageInfo")
	FStageQuestInfo GetStageQuestInfo() const;

	UFUNCTION()
	void EnemyKilledCount();

	void NotifyActorDestroyed(const AActor* DestroyedActor);

protected :
	FTimerHandle CountdownHandle;
	
	int32 Timer = 0;
	int32 KilledCount = 0;
	int32 TargetKilledCount = 0;
	void TimerCountdown();

	bool bPreparePhase = true;
	bool bActionPhase = false;
};
