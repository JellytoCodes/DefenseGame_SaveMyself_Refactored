// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SaveMyselfCharacterBase.h"
#include "Enemy/FSM/NormalEnemyFSM.h"
#include "SaveMyselfEnemy.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathDelegate);

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
	virtual void DotDamagedEvent_Implementation(const float Damage) override;
	virtual void SlowMovementEvent_Implementation(const float CurEffect) override;
	virtual void UnDotDamagedEvent_Implementation() override;
	/* end Combat Interface */

	/* Effect TimerHandle */
	FTimerHandle BindingTime;
	FTimerHandle DotDamageTime;
	FTimerHandle SlowMovementTime;
	/* end Effect TimerHandle*/

	FOnDeathDelegate OnDeathDelegate;

	UFUNCTION(BlueprintPure)
	float GetCurrentHP() const { return EnemyComponent->CurrentHp; }

	UFUNCTION(BlueprintPure)
	float GetMaxHP() const { return EnemyComponent->EnemyInformation.MaxHP; }

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHPProgressBar();

protected :
	virtual void Die() override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UNormalEnemyFSM> EnemyComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ANormalEnemyAIController> EnemyAIController;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetComponent")
	TSubclassOf<UEffectWidgetComponent> EffectWidgetComponentClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UEffectWidgetComponent> EffectWidgetComponent;

	void BlackboardInitialize() const;

	UFUNCTION()
	void SetIsPlayerState();
};
