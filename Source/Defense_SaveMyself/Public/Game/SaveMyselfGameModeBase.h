// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameFramework/GameModeBase.h"
#include "SaveMyselfGameModeBase.generated.h"

class UDataTable;
class USaveMyselfStageInfo;

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public :
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	const USaveMyselfStageInfo* GetStageInfoAsset() const { return StageInfoAsset; }

protected :

	UPROPERTY(EditDefaultsOnly, Category = "Game Setup")
	TArray<TObjectPtr<USaveMyselfStageInfo>> StageAssets;

	UPROPERTY(EditDefaultsOnly, Category = "Game Setup")
	TObjectPtr<UDataTable> ItemDataRow;

	UPROPERTY()
	TObjectPtr<USaveMyselfStageInfo> StageInfoAsset;

	
};
