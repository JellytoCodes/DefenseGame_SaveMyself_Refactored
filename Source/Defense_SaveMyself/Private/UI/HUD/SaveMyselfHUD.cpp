
#include "UI/HUD/SaveMyselfHUD.h"

#include "UI/Widget/SavemyselfUserWidget.h"

void ASaveMyselfHUD::InitPlayerQuickSlot()
{
	if (PlayerQuickSlotClass)
	{
		if (PlayerQuickSlotInstance == nullptr)
		{
			PlayerQuickSlotInstance = CreateWidget<USavemyselfUserWidget>(GetWorld(), PlayerQuickSlotClass);
			PlayerQuickSlotInstance->AddToViewport();
		}
	}
}

void ASaveMyselfHUD::InitStageInfoWidget()
{
	if (StageInfoClass)
	{
		if (StageInfoInstance == nullptr)
		{
			StageInfoInstance = CreateWidget<USavemyselfUserWidget>(GetWorld(), StageInfoClass);
			StageInfoInstance->AddToViewport();
		}
	}
}

void ASaveMyselfHUD::InitPauseMenu()
{
	if (PauseMenuClass)
	{
		if (PauseMenuInstance == nullptr)
		{
			PauseMenuInstance = CreateWidget<USavemyselfUserWidget>(GetWorld(), PauseMenuClass);
			PauseMenuInstance->AddToViewport();
			PauseMenuInstance->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ASaveMyselfHUD::VisiblePauseMenu() const
{
	if (PauseMenuInstance == nullptr) return;
	PauseMenuInstance->SetVisibility(ESlateVisibility::Visible);
}

void ASaveMyselfHUD::HidePauseMenu() const
{
	if (PauseMenuInstance == nullptr) return;
	PauseMenuInstance->SetVisibility(ESlateVisibility::Hidden);
}

void ASaveMyselfHUD::HidePlayerQuickSlot() const
{
	if (PlayerQuickSlotInstance == nullptr) return;
	PlayerQuickSlotInstance->SetVisibility(ESlateVisibility::Hidden);
}

void ASaveMyselfHUD::HideStageInfoWidget() const
{
	if (StageInfoInstance == nullptr) return;
	StageInfoInstance->SetVisibility(ESlateVisibility::Hidden);
}
