// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SaveMyselfCharacterBase.h"
#include "SaveMyselfEnemy.generated.h"

class UEffectWidgetComponent;
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
	virtual void BeginPlay() override;

	/* Combat Interface */
	virtual void BindingEvent_Implementation(const float CurEffect) override;
	virtual void DamagedEvent_Implementation(const float Damage) override;
	/* End Combat Interface */

protected :
	virtual void Die() override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UNormalEnemyFSM> EnemyComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ANormalEnemyAIController> EnemyAIController;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetComponent")
	TSubclassOf<UEffectWidgetComponent> EffectWidgetComponentClass;

	UPROPERTY()
	TObjectPtr<UEffectWidgetComponent> EffectWidgetComponent;

	void BlackboardInitialize() const;

	UFUNCTION()
	void SetIsPlayerDead();
};
