// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NormalEnemyAIController.generated.h"

class UNormalEnemyFSM;
class ASaveMyselfEnemy;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

struct FAIStimulus;

UCLASS()
class DEFENSE_SAVEMYSELF_API ANormalEnemyAIController : public AAIController
{
	GENERATED_BODY()

public :
	ANormalEnemyAIController();

	void HandleIdle();
	void HandlePatrol();
	void HandleChase();
	void HandleAttack();

	void EvaluateState();

protected :

	virtual void OnPossess(APawn* InPawn) override;

private :

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "Perception", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASaveMyselfEnemy> EnemyActor;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "Perception", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "Perception", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	int32 regionIndex = 0;


};
