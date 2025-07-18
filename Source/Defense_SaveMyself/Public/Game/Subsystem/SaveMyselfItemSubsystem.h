#pragma once

#include "CoreMinimal.h"
#include "Data/SaveMyselfItemInfo.h"
#include "Data/SaveMyselfStageInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
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
class DEFENSE_SAVEMYSELF_API USaveMyselfItemSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public :
	void BuildCache(const USaveMyselfStageInfo* StageAsset);
	void SetDataTable(UDataTable* DataTable);

	const TArray<FWidgetSlotDataInfo>& GetWarehouseSlotInfoInfo() const { return WarehouseSlotInfo; }
	const TArray<FWidgetSlotDataInfo>& GetPlayerQuickSlotData() const { return PlayerQuickSlotData; }
	const float GetCurrentBagWeight() const { return CurrentBagWeight; }

	UFUNCTION(BlueprintPure, meta = (WorldContext="WorldContext"))
	static USaveMyselfItemSubsystem* GetItemSubSystem(const UObject* WorldContext);

	void AddItem(const FWidgetSlotDataInfo& NewItem);
	void DecrementItem(const FWidgetSlotDataInfo& RemoveItem);

	UFUNCTION()
	void GetQuickSlotIndexItemData(const int32 SlotIndex);

	void RegisterSpawnComponent(UActorSpawnComponent* SpawnComp);

	UPROPERTY(BlueprintAssignable, Category = "Subsystem|AddItem")
	FItemDataUpdateSignature AddItemDataDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Subsystem|DecrementItem")
	FItemDataUpdateSignature DecrementItemDataDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Subsystem|UseItem")
	FItemDataUpdateSignature UseItemDataDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Subsystem|ExportData")
	FExportItemDataDelegate ExportItemDataDelegate;

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
};

template <typename T>
T* USaveMyselfItemSubsystem::GetItemDataRow(FName ItemName) const
{
	return ItemDataTable->FindRow<T>(ItemName, TEXT("Not Data"));
}
