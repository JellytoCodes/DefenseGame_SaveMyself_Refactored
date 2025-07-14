
#include "UI/WidgetController/SaveMyselfWidgetController.h"
#include "Components/WrapBox.h"
#include "Game/SaveMyselfGameModeBase.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"
#include "UI/Widget/SavemyselfUserWidget.h"

void USaveMyselfWidgetController::UpdateWarehouseWidget(UWrapBox* WrapBox)
{
	if (const auto* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
	{
		const TArray<FWidgetSlotDataInfo>& Data = ItemSubsystem->GetWarehouseSlotInfoInfo();
		const int32 ChildCnt = WrapBox->GetChildrenCount();

		for (int32 i = 0 ; i < ChildCnt ; ++i)
		{
			if (USavemyselfUserWidget* Slot = Cast<USavemyselfUserWidget>(WrapBox->GetChildAt(i)))
			{
				if (Data.IsValidIndex(i))
				{
					Slot->SetItemData(Data[i]);
				}
				else
				{
					return;
				}
			}
		}
	}
}

const float USaveMyselfWidgetController::GetMaxBagWeight() const
{
	if (ASaveMyselfGameModeBase* ModeBase = Cast<ASaveMyselfGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		return ModeBase->GetStageInfoAsset()->MaxBagWidget;
	}
	return 0;
}

const float USaveMyselfWidgetController::GetCurrentBagWeight() const
{
	if (auto* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
	{
		return ItemSubsystem->GetCurrentBagWeight();
	}
	return 0;
}

void USaveMyselfWidgetController::UpdateAddPlayerItemData(const FWidgetSlotDataInfo& UpdateItem)
{
	if (auto* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
	{
		ItemSubsystem->AddItem(UpdateItem);
	}
}

void USaveMyselfWidgetController::UpdateRemovePlayerItemData(const FWidgetSlotDataInfo& UpdateItem)
{
	if (auto* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
	{
		ItemSubsystem->DecrementItem(UpdateItem);
	}
}

int32 USaveMyselfWidgetController::UpdatePlayerQuickSlotWidget(UWrapBox* WrapBox)
{
	if (const auto* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
	{
		const TArray<FWidgetSlotDataInfo>& Data = ItemSubsystem->GetPlayerQuickSlotData();
		const int32 ChildCnt = WrapBox->GetChildrenCount();

		for (int32 i = 0 ; i < ChildCnt ; ++i)
		{
			if (USavemyselfUserWidget* Slot = Cast<USavemyselfUserWidget>(WrapBox->GetChildAt(i)))
			{
				if (Data.IsValidIndex(i))
				{
					Slot->SetItemData(Data[i]);
				}
				else
				{
					return i;
				}
			}
		}
	}
	return 0;
}
