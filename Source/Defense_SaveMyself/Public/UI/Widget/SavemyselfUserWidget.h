// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/SaveMyselfItemInfo.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"
#include "SavemyselfUserWidget.generated.h"

UCLASS()
class DEFENSE_SAVEMYSELF_API USavemyselfUserWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintImplementableEvent, Category = "ItemSlot")
	void SetItemData(const FWidgetSlotDataInfo& SlotData);
};
