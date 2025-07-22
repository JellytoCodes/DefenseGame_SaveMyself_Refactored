// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NormalEnemyAIController.generated.h"

class UBehaviorTreeComponent;
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

protected :
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "AI")
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "AI")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTree;
};
