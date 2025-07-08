// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/SaveMyselfItemInfo.h"
#include "SaveMyselfWidgetController.generated.h"

struct FWidgetSlotDataInfo;

class UWrapBox;

UCLASS(BlueprintType, Blueprintable)
class DEFENSE_SAVEMYSELF_API USaveMyselfWidgetController : public UObject
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintCallable, Category = "UI|Warehouse")
	void AddItemWarehouseWidget(UWrapBox* WrapBox);
};
