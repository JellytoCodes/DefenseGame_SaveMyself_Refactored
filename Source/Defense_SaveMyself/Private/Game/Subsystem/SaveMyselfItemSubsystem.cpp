// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Subsystem/SaveMyselfItemSubsystem.h"

void USaveMyselfItemSubsystem::BuildCache(const USaveMyselfStageInfo* StageAsset)
{
	StageItemInfo.Reset();
	StageItemCache.Reset();
	WidgetSlotInfo.Reset();
	WidgetSlotInfo.SetNum(StageAsset->SetStageItem.Num());
	int i = 0;

	for(const FStageItemInfo& Info : StageAsset->SetStageItem)
	{
		StageItemInfo.Add(Info);
		
		if (const FItemInformation* Row = GetItemDataRow<FItemInformation>(Info.ItemName))
		{
			StageItemCache.Add(*Row);
			WidgetSlotInfo[i].ItemName = Row->ItemName;
			WidgetSlotInfo[i].Quantity = Info.ItemQuantity;
			WidgetSlotInfo[i].NameDisplay = Row->NameDisplay;
			WidgetSlotInfo[i].Description = Row->Description;
			WidgetSlotInfo[i].TypeDisplay = Row->TypeDisplay;
			i++;
		}
	}
}

void USaveMyselfItemSubsystem::SetDataTable(UDataTable* DataTable)
{
	ItemDataTable = DataTable;
}

USaveMyselfItemSubsystem* USaveMyselfItemSubsystem::GetItemSubSystem(const UObject* WorldContext)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull))
	{
		
		if (UGameInstance* GI = World->GetGameInstance())
		{
			return GI->GetSubsystem<USaveMyselfItemSubsystem>();		
		}
	}
	return nullptr;	
}
