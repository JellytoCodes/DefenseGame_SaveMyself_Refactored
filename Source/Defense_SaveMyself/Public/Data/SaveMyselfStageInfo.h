#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SaveMyselfStageInfo.generated.h"

USTRUCT(BlueprintType)
struct FStageItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Stage Item")
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "Stage Item")
	int32 ItemQuantity;
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

	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	float PrepareTime;

	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	float ActionTime;

	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	float MaxBagWidget;

	UPROPERTY(EditDefaultsOnly, Category = "StageData")
	TArray<FStageItemInfo> SetStageItem;
};
