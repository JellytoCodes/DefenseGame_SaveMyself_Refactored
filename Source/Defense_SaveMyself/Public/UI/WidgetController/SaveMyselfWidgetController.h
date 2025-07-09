// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveMyselfWidgetController.generated.h"

class UWrapBox;
struct FWidgetSlotDataInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlotDataInfoSigniture);


UCLASS(BlueprintType, Blueprintable)
class DEFENSE_SAVEMYSELF_API USaveMyselfWidgetController : public UObject
{
	GENERATED_BODY()

public :
	/** Warehouse */
	UFUNCTION(BlueprintCallable, Category = "UI|Warehouse")
	void AddItemWarehouseWidget(UWrapBox* WrapBox);


	UFUNCTION(BlueprintCallable, Category = "UI|Warehouse")
	const float GetMaxBagWeight() const;

	/** Player QuickSlot */
	UFUNCTION(BlueprintCallable, Category = "UI|PlayerQuickSlot")
	void AddItemPlayerQuickSlotWidget(UWrapBox* WrapBox);

	UFUNCTION(BlueprintCallable, Category = "UI|PlayerQuickSlot")
	void UpdateAddPlayerItemData(const FWidgetSlotDataInfo& UpdateItem);

	FOnSlotDataInfoSigniture OnSlotDataInfoDelegate;
};
