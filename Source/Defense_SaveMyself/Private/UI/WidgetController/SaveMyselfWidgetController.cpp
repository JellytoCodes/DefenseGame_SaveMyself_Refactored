
#include "UI/WidgetController/SaveMyselfWidgetController.h"

#include "Components/WrapBox.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/SavemyselfUserWidget.h"

void USaveMyselfWidgetController::AddItemWarehouseWidget(UWrapBox* WrapBox)
{
	if (const auto* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
	{
		const TArray<FWidgetSlotDataInfo>& Data = ItemSubsystem->GetWidgetSlotInfo();
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
