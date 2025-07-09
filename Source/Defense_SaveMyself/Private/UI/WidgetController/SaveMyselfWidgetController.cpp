
#include "UI/WidgetController/SaveMyselfWidgetController.h"
#include "Components/WrapBox.h"
#include "Game/SaveMyselfGameModeBase.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"
#include "UI/Widget/SavemyselfUserWidget.h"

void USaveMyselfWidgetController::AddItemWarehouseWidget(UWrapBox* WrapBox)
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
					Slot->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					Slot->SetVisibility(ESlateVisibility::Hidden);
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

void USaveMyselfWidgetController::UpdateAddPlayerItemData(const FWidgetSlotDataInfo& UpdateItem)
{
	if (auto* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
	{
		ItemSubsystem->AddItem(UpdateItem);
	}
}

void USaveMyselfWidgetController::AddItemPlayerQuickSlotWidget(UWrapBox* WrapBox)
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
					Slot->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					Slot->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}
	}
}