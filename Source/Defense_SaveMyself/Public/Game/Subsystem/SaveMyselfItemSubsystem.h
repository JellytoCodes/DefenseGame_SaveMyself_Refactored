// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/SaveMyselfItemInfo.h"
#include "Data/SaveMyselfStageInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveMyselfItemSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FWidgetSlotDataInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemSlot Data")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemSlot Data")
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSlot Data")
	FText NameDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSlot Data")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSlot Data")
	FText TypeDisplay;
};

UCLASS()
class DEFENSE_SAVEMYSELF_API USaveMyselfItemSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public :

	void BuildCache(const USaveMyselfStageInfo* StageAsset);
	void SetDataTable(UDataTable* DataTable);

	const TArray<FWidgetSlotDataInfo>& GetWidgetSlotInfo() const { return WidgetSlotInfo; }

	UFUNCTION(BlueprintPure, meta =(WorldContext="WorldContext"))
	static USaveMyselfItemSubsystem* GetItemSubSystem(const UObject* WorldContext);

protected :
	template<typename T>
	T* GetItemDataRow(FName ItemName) const;

	UPROPERTY()
	UDataTable* ItemDataTable;

	TArray<FItemInformation> StageItemCache;
	TArray<FStageItemInfo> StageItemInfo;
	TArray<FWidgetSlotDataInfo> WidgetSlotInfo;
};

template <typename T>
T* USaveMyselfItemSubsystem::GetItemDataRow(FName ItemName) const
{
	return ItemDataTable->FindRow<T>(ItemName, TEXT("Not Data"));
}
