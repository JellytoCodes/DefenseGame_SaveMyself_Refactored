
#include "UI/HUD/SaveMyselfHUD.h"

#include "UI/Widget/SavemyselfUserWidget.h"

void ASaveMyselfHUD::InitPlayerQuickSlot()
{
	if (PlayerQuickSlotClass)
	{
		PlayerQuickSlotInstance = CreateWidget<USavemyselfUserWidget>(GetWorld(), PlayerQuickSlotClass);
		if (!PlayerQuickSlotInstance) return;

		PlayerQuickSlotInstance->AddToViewport();
	}
}
