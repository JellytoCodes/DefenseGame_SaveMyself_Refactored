#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SaveMyselfStageInfo.generated.h"

UENUM(BlueprintType)
enum class EStageQuestType : uint8
{
	None,
	EnemyAllKill,
	TargetDestroy,
	TimeLimit
};

USTRUCT(BlueprintType)
struct FStageItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Stage Item")
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "Stage Item")
	int32 ItemQuantity;
};

USTRUCT(BlueprintType)
struct FStageQuestInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EStageQuestType QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<AActor>> DestroyTargets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText StageQuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 KilledEnemies = 0;
};

UCLASS()
class DEFENSE_SAVEMYSELF_API USaveMyselfStageInfo : public UDataAsset
{
	GENERATED_BODY()

public :
	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	FName CurStage;

	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	FName NextStage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CurStageText;

	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	int32 PrepareTime;

	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	int32 ActionTime;

	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	float MaxBagWidget;

	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	TArray<FStageItemInfo> SetStageItem;

	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	FStageQuestInfo CurrentStageQuestInfo;
};
