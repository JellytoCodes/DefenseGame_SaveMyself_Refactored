// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SaveMyselfItemInfo.generated.h"

class UTexture2D;
class ASaveMyselfActor;
class UStaticMesh;

UENUM(BlueprintType)
enum class EItemTypes : uint8
{
	None,
	Weapon,
	Structure,
	Trap,
};

UENUM(BlueprintType)
enum class EEffectTypes : uint8
{
	None,
	SingleDamage,
	Explosive,
	Bind
};

USTRUCT(BlueprintType)
struct FItemInformation : public FTableRowBase
{
	GENERATED_BODY()

	FItemInformation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	EItemTypes ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	float EffectValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	float EffectRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	EEffectTypes EffectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	TSubclassOf<ASaveMyselfActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	float ItemWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	FText NameDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	FText TypeDisplay;
};


