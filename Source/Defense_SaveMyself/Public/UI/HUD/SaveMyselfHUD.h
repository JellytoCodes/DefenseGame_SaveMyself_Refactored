// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SaveMyselfHUD.generated.h"

class USavemyselfUserWidget;

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfHUD : public AHUD
{
	GENERATED_BODY()

public :
	void InitPlayerQuickSlot();
	void InitStageInfoWidget();
	void InitPauseMenu();

	void VisiblePauseMenu() const;

	void HidePlayerQuickSlot() const;
	void HideStageInfoWidget() const;
	void HidePauseMenu() const;

private :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Setting", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USavemyselfUserWidget> PlayerQuickSlotClass;

	UPROPERTY()
	TObjectPtr<USavemyselfUserWidget> PlayerQuickSlotInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Setting", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USavemyselfUserWidget> StageInfoClass;

	UPROPERTY()
	TObjectPtr<USavemyselfUserWidget> StageInfoInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Setting", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USavemyselfUserWidget> PauseMenuClass;

	UPROPERTY()
	TObjectPtr<USavemyselfUserWidget> PauseMenuInstance;

};
