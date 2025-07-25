#pragma once

#include "CoreMinimal.h"
#include "Data/SaveMyselfItemInfo.h"
#include "Data/SaveMyselfStageInfo.h"
#include "Subsystems/WorldSubsystem.h"
#include "SaveMyselfItemSubsystem.generated.h"

class UActorSpawnComponent;

USTRUCT(BlueprintType)
struct FWidgetSlotDataInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemSlot Data")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemSlot Data")
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemSlot Data")
	float ItemWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSlot Data")
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSlot Data")
	FText NameDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSlot Data")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSlot Data")
	FText TypeDisplay;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemDataUpdateSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExportItemDataDelegate, const FItemInformation&, UseItem);
UCLASS()
class DEFENSE_SAVEMYSELF_API USaveMyselfItemSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public :
	void BuildCache(const USaveMyselfStageInfo* StageAsset);
	void SetDataTable(UDataTable* DataTable);

	const TArray<FWidgetSlotDataInfo>& GetWarehouseSlotInfoInfo() const { return WarehouseSlotInfo; }
	const TArray<FWidgetSlotDataInfo>& GetPlayerQuickSlotData() const { return PlayerQuickSlotData; }
	float GetCurrentBagWeight() const { return CurrentBagWeight; }

	FItemInformation* GetItemInfo(const FName ItemName);

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContext"))
	static USaveMyselfItemSubsystem* GetItemSubSystem(const UObject* WorldContext);

	void AddItem(const FWidgetSlotDataInfo& NewItem);
	void DecrementItem(const FWidgetSlotDataInfo& RemoveItem);

	UFUNCTION()
	void GetQuickSlotIndexItemData(const int32 SlotIndex);

	void RegisterSpawnComponent(UActorSpawnComponent* SpawnComp);

	int32 GetQuickSlotQuantity(const FName ItemName);

	UPROPERTY(BlueprintAssignable, Category = "Subsystem|AddItem")
	FItemDataUpdateSignature AddItemDataDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Subsystem|DecrementItem")
	FItemDataUpdateSignature DecrementItemDataDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Subsystem|UseItem")
	FItemDataUpdateSignature UseItemDataDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Subsystem|ExportData")
	FExportItemDataDelegate ExportItemDataDelegate;

	UFUNCTION(BlueprintPure)
	bool GetWarehouseEntrance() const { return bWarehouseEntrance; }

	UFUNCTION(BlueprintCallable)
	void SetWarehouseEntrance(const bool InIsEntrance) { bWarehouseEntrance = InIsEntrance; }

protected :	

	UFUNCTION()
	void HandleActorSpawnConfirmed(const FItemInformation& SPawnedItem);

	template<typename T>
	T* GetItemDataRow(FName ItemName) const;

	UPROPERTY()
	UDataTable* ItemDataTable;

	TMap<FName, FItemInformation> StageItemCache;
	TArray<FStageItemInfo> StageItemInfo;
	TArray<FWidgetSlotDataInfo> WarehouseSlotInfo;
	TArray<FWidgetSlotDataInfo> PlayerQuickSlotData;

	float CurrentBagWeight = 0;

	bool bWarehouseEntrance = false;
};

template <typename T>
T* USaveMyselfItemSubsystem::GetItemDataRow(FName ItemName) const
{
	return ItemDataTable->FindRow<T>(ItemName, TEXT("Not Data"));
}
