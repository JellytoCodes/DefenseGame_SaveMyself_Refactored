// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveMyselfActor.generated.h"

struct FItemInformation;
class UActorEffectComponent;
class UBoxComponent;

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASaveMyselfActor();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool GetDamaged(const float InDamage);

	UFUNCTION(BlueprintCallable)
	void SetStructureHP(const float InStructureHP);

	UFUNCTION(BlueprintPure)
	FItemInformation& GetItemInfo() const { return *ItemInfo; }

protected :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Setting")
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Setting")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Setting")
	TObjectPtr<UMaterialInterface> CanPlaceMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Setting")
	TObjectPtr<UMaterialInterface> CannotPlaceMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Setting")
	TObjectPtr<UActorEffectComponent> ActorEffectComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StimuliSource")
	class UAIPerceptionStimuliSourceComponent* StimuliSourceComp;

	float StructureHP = 0;

	FItemInformation* ItemInfo;

	UPROPERTY(EditDefaultsOnly)
	FName ItemName;
};
