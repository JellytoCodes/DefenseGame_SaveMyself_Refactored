// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveMyselfWidgetController.generated.h"

class UWrapBox;
struct FWidgetSlotDataInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlotDataInfoSigniture);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSortPlayerQuickSlotSignature);

UCLASS(BlueprintType, Blueprintable)
class DEFENSE_SAVEMYSELF_API USaveMyselfWidgetController : public UObject
{
	GENERATED_BODY()

public :
	/** Warehouse */
	UFUNCTION(BlueprintCallable, Category = "UI|Warehouse")
	void UpdateWarehouseWidget(UWrapBox* WrapBox);

	UFUNCTION(BlueprintCallable, Category = "UI|Warehouse")
	const float GetMaxBagWeight() const;

	UFUNCTION(BlueprintCallable, Category = "UI|Warehouse")
	const float GetCurrentBagWeight() const;

	/** Player QuickSlot */
	UFUNCTION(BlueprintCallable, Category = "UI|PlayerQuickSlot")
	int32 UpdatePlayerQuickSlotWidget(UWrapBox* WrapBox);

	UFUNCTION(BlueprintCallable, Category = "UI|PlayerQuickSlot")
	void UpdateAddPlayerItemData(const FWidgetSlotDataInfo& UpdateItem);

	UFUNCTION(BlueprintCallable, Category = "UI|PlayerQuickSlot")
	void UpdateRemovePlayerItemData(const FWidgetSlotDataInfo& UpdateItem);

	FOnSlotDataInfoSigniture OnSlotDataInfoDelegate;
};
