// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/SaveMyselfItemInfo.h"
#include "ActorSpawnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConfirmActorSpawnDelegate, const FItemInformation&, SpawnItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmPlace, bool, CheckPlace);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEFENSE_SAVEMYSELF_API UActorSpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public :	
	UActorSpawnComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ConfirmPlacement();

	UPROPERTY(BlueprintAssignable)
	FConfirmActorSpawnDelegate ConfirmActorSpawnDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnConfirmPlace OnConfirmPlace;

protected :
	virtual void BeginPlay() override;

	void SpawnedProjectile() const;
	void SpawnedTrapAndStructure();

	void DisableEquippedItem() const;

private :
	UFUNCTION()
	void GetSpawnItemData(const FItemInformation& ItemData);

	FItemInformation SpawnItemData;

	bool bCanPlaceConfirm = false;

	bool TraceToGround(FHitResult& HitResult) const;
	void CreatePreviewActor();
	void SetGhostMaterial(const bool bCanPlace) const;

	UPROPERTY()
	AActor* PreviewActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Preview")
	float GridSize = 50.f;

	UPROPERTY(EditAnywhere, Category = "Preview")
	UMaterialInstance* CanPlaceMaterial;

	UPROPERTY(EditAnywhere, Category = "Preview")
	UMaterialInstance* CannotPlaceMaterial;

	UPROPERTY(EditDefaultsOnly)
	FVector SpawnZeroVector = FVector::ZeroVector;
};
