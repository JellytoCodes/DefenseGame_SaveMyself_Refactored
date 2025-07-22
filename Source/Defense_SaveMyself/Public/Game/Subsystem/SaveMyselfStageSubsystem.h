#pragma once

#include "CoreMinimal.h"
#include "Data/SaveMyselfStageInfo.h"
#include "Subsystems/WorldSubsystem.h"
#include "SaveMyselfStageSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseTimerHandleSignature, int32, Timer);
DECLARE_MULTICAST_DELEGATE(FOnPhaseStateHandleSignature);

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
	int32 StageNum = 0;
};

UCLASS()
class DEFENSE_SAVEMYSELF_API USaveMyselfStageSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public :
	void BuildCache(const USaveMyselfStageInfo* StageAsset);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContext"))
	static USaveMyselfStageSubsystem* GetStageSubsystem(const UObject* WorldContext);

	FCurrentStageInfo CurrentStageInfo;

	UFUNCTION(BlueprintCallable, Category = "StageInfo|PreparePhase")
	void PreparePhaseCountdown();

	UFUNCTION(BlueprintCallable, Category = "StageInfo|ActionPhase")
	void ActionPhaseCountdown();

	UFUNCTION(BlueprintCallable, Category = "StageInfo|ClearTimer")
	void ClearCountdown();

	UFUNCTION(BlueprintPure, Category = "StageInfo")
	int32 GetStageNum() const;

	UFUNCTION(BlueprintPure, Category = "StageInfo")
	FText GetQuestDescription() const;

	UFUNCTION(BlueprintPure, Category = "StageInfo")
	bool GetPreparePhase() const;

	UPROPERTY(BlueprintAssignable)
	FOnPhaseTimerHandleSignature OnPrepareTimerHandleDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPhaseTimerHandleSignature OnActionTimerHandleDelegate;

	FOnPhaseStateHandleSignature OnActionPhaseDelegate;

protected :
	FTimerHandle CountdownHandle;
	
	int32 Timer = 0;

	void TimerCountdown();

	bool bPreparePhase = true;
	bool bActionPhase = false;
};
