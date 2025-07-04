// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SaveMyselfCharacterBase.h"
#include "SaveMyselfEnemy.generated.h"

class UNormalEnemyFSM;

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfEnemy : public ASaveMyselfCharacterBase
{
	GENERATED_BODY()

public :
	ASaveMyselfEnemy();
	UNormalEnemyFSM* GetEnemyFSMComponent();

private :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Perception", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNormalEnemyFSM> EnemyComponent;
};
