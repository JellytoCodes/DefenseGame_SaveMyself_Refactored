// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Subsystem/SaveMyselfItemSubsystem.h"

#include "Components/ActorSpawnComponent.h"
#include "Engine/Engine.h"

void USaveMyselfItemSubsystem::RegisterSpawnComponent(UActorSpawnComponent* SpawnComp)
{
	if (SpawnComp)
	{
		SpawnComp->ConfirmActorSpawnDelegate.AddUObject(this, &USaveMyselfItemSubsystem::HandleActorSpawnConfirmed);
	}
}

int32 USaveMyselfItemSubsystem::GetQuickSlotQuantity(const FName ItemName)
{
	for (FWidgetSlotDataInfo& Pair : PlayerQuickSlotData)
	{
		if (Pair.ItemName == ItemName) return Pair.Quantity;
	}
	return 0;
}

void USaveMyselfItemSubsystem::HandleActorSpawnConfirmed(const FItemInformation& SPawnedItem)
{
	for (int32 i = 0 ; i < PlayerQuickSlotData.Num() ; ++i)
	{
		if (PlayerQuickSlotData[i].ItemName == SPawnedItem.ItemName)
		{
			if (PlayerQuickSlotData[i].Quantity > 1)
			{
				PlayerQuickSlotData[i].Quantity--;
			}
			else
			{
				PlayerQuickSlotData.RemoveAt(i);
			}
			break;
		}
	}

	UseItemDataDelegate.Broadcast();
}

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
			StageItemCache.Add(Info.ItemName, *Row);
			WarehouseSlotInfo[i].ItemName = Row->ItemName;
			WarehouseSlotInfo[i].Quantity = Info.ItemQuantity;
			WarehouseSlotInfo[i].ItemIcon = Row->ItemIcon;
			WarehouseSlotInfo[i].NameDisplay = Row->NameDisplay;
			WarehouseSlotInfo[i].Description = Row->Description;
			WarehouseSlotInfo[i].TypeDisplay = Row->TypeDisplay;
			WarehouseSlotInfo[i].ItemWeight = Row->ItemWeight;
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
	//창고 아이템 조회 후 수량 감소 처리
	for (auto& WarehouseData : WarehouseSlotInfo)
	{
		if (WarehouseData.ItemName == NewItem.ItemName && WarehouseData.Quantity > 0)
		{
			WarehouseData.Quantity--;
			break;
		}
	}

	//신규 아이템 유무 체크
	bool bIsNewItem = true;

	//플레이어 퀵슬롯 아이템 조회 후 수량 증가 처리
	for (auto& PlayerData : PlayerQuickSlotData)
	{
		if (PlayerData.ItemName == NewItem.ItemName)
		{
			PlayerData.Quantity++;
			bIsNewItem = false;
			break;
		}
	}

	//신규 아이템일 경우 슬롯에 데이터 추가
	if (bIsNewItem)
	{
		PlayerQuickSlotData.Add(FWidgetSlotDataInfo
		{
			.ItemName = NewItem.ItemName,
			.Quantity = 1,
			.ItemWeight = NewItem.ItemWeight,
			.ItemIcon = NewItem.ItemIcon,
			.NameDisplay = NewItem.NameDisplay,
			.Description = NewItem.Description,
			.TypeDisplay = NewItem.TypeDisplay
		});	
	}

	CurrentBagWeight += NewItem.ItemWeight;
	AddItemDataDelegate.Broadcast();
}

void USaveMyselfItemSubsystem::DecrementItem(const FWidgetSlotDataInfo& RemoveItem)
{
	for (int32 i = 0 ; i < PlayerQuickSlotData.Num() ; ++i)
	{
		if (PlayerQuickSlotData[i].ItemName == RemoveItem.ItemName)
		{
			if (PlayerQuickSlotData[i].Quantity > 1)
			{
				PlayerQuickSlotData[i].Quantity--;
			}
			else
			{
				PlayerQuickSlotData.RemoveAt(i);	
			}
			break;
		}
	}

	for (auto& WarehouseData : WarehouseSlotInfo)
	{
		if (WarehouseData.ItemName == RemoveItem.ItemName)
		{
			WarehouseData.Quantity++;
			break;
		}
	}

	CurrentBagWeight -= RemoveItem.ItemWeight;
	DecrementItemDataDelegate.Broadcast();
}

void USaveMyselfItemSubsystem::GetQuickSlotIndexItemData(const int32 SlotIndex)
{
	if (!PlayerQuickSlotData.IsValidIndex(SlotIndex))
	{
		ExportItemDataDelegate.Broadcast(FItemInformation());
		return;
	}

	const FName ItemName = PlayerQuickSlotData[SlotIndex].ItemName;
	const FItemInformation* FoundItem = StageItemCache.Find(ItemName);

	if (FoundItem)
	{
		ExportItemDataDelegate.Broadcast(*FoundItem);
	}
}



