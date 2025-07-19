
#include "Game/SaveMyselfGameModeBase.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"

void ASaveMyselfGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	FString PureMap = FPackageName::GetShortName(MapName);

	int32 Underscore = PureMap.Find(TEXT("_Stage_"));
	FString StagePart = PureMap.Mid(Underscore + 1);

	//�������� ��ȣ ����
	int32 StageID = FCString::Atoi(*StagePart.RightChop(6));
	check(StageID > 0);
	
	StageInfoAsset = StageAssets[StageID - 1] ? StageAssets[StageID - 1] : nullptr;
	if (StageInfoAsset && ItemDataRow)
	{
		if (auto* ItemSubsystem = GetGameInstance()->GetSubsystem<USaveMyselfItemSubsystem>())
		{
			ItemSubsystem->SetDataTable(ItemDataRow);	
			ItemSubsystem-> BuildCache(StageInfoAsset);
		}
		if (auto* StageSubsystem = GetGameInstance()->GetSubsystem<USaveMyselfStageSubsystem>())
		{
			StageSubsystem->BuildCache(StageInfoAsset);
		}
	}
}
