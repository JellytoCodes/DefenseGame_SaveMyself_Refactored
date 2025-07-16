// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SaveMyselfCharacterBase.h"
#include "SaveMyselfEnemy.generated.h"

class ANormalEnemyAIController;
class UBehaviorTree;
class UNormalEnemyFSM;

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfEnemy : public ASaveMyselfCharacterBase
{
	GENERATED_BODY()

public :
	ASaveMyselfEnemy();
	UNormalEnemyFSM* GetEnemyFSMComponent();

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetEnemyMesh() {return GetMesh(); }

protected :
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UNormalEnemyFSM> EnemyComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ANormalEnemyAIController> EnemyAIController;
};
