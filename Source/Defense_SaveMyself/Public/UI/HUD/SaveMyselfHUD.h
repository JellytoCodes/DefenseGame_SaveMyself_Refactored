// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SaveMyselfHUD.generated.h"

class USavemyselfUserWidget;
/**
 * 
 */
UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfHUD : public AHUD
{
	GENERATED_BODY()

public :
	void InitPlayerQuickSlot();

private :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Setting", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USavemyselfUserWidget> PlayerQuickSlotClass;

	UPROPERTY()
	TObjectPtr<USavemyselfUserWidget> PlayerQuickSlotInstance;

};
