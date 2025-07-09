// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Subsystem/SaveMyselfItemSubsystem.h"

#include "Engine/Engine.h"

void USaveMyselfItemSubsystem::BuildCache(const USaveMyselfStageInfo* StageAsset)
{
	StageItemInfo.Reset();
	StageItemCache.Reset();
	WarehouseSlotInfo.Reset();
	WarehouseSlotInfo.SetNum(StageAsset->SetStageItem.Num());
	int i = 0;

	for(const FStageItemInfo& Info : StageAsset->SetStageItem)
	{
		StageItemInfo.Add(Info);
		
		if (const FItemInformation* Row = GetItemDataRow<FItemInformation>(Info.ItemName))
		{
			StageItemCache.Add(*Row);
			WarehouseSlotInfo[i].ItemName = Row->ItemName;
			WarehouseSlotInfo[i].Quantity = Info.ItemQuantity;
			WarehouseSlotInfo[i].ItemIcon = Row->ItemIcon;
			WarehouseSlotInfo[i].NameDisplay = Row->NameDisplay;
			WarehouseSlotInfo[i].Description = Row->Description;
			WarehouseSlotInfo[i].TypeDisplay = Row->TypeDisplay;
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

void USaveMyselfItemSubsystem::AddItem(const FWidgetSlotDataInfo& NewItem)
{
	for (auto& PlayerData : PlayerQuickSlotData)
	{
		if (PlayerData.ItemName == NewItem.ItemName)
		{
			PlayerData.Quantity++;
			PlayerQuickSlotUpdateDelegate.Broadcast();
			return;
		}
	}



	PlayerQuickSlotData.Add(FWidgetSlotDataInfo
	{
		.ItemName = NewItem.ItemName,
		.Quantity = 1,
		.NameDisplay = NewItem.NameDisplay,
		.Description = NewItem.Description,
		.TypeDisplay = NewItem.TypeDisplay
	});
	
	PlayerQuickSlotUpdateDelegate.Broadcast();
}