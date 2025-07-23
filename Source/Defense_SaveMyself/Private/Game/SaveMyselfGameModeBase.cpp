
#include "Game/SaveMyselfGameModeBase.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"

void ASaveMyselfGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	FString PureMap = FPackageName::GetShortName(MapName);

	int32 Underscore = PureMap.Find(TEXT("_Stage_"));
	FString StagePart = PureMap.Mid(Underscore + 1);

	for (const TTuple<FName, TObjectPtr<USaveMyselfStageInfo>>& StageData : StageAssets)
	{
		if (StageData.Key == StagePart)
		{
			StageName = StageData.Key;
			StageInfoAsset = StageData.Value;
			if (auto* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
			{
				ItemSubsystem->SetDataTable(ItemDataRow);	
				ItemSubsystem->BuildCache(StageInfoAsset);
			}
			if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
			{
				StageSubsystem->BuildCache(StageInfoAsset);
			}
			break;
		}
	}
}
