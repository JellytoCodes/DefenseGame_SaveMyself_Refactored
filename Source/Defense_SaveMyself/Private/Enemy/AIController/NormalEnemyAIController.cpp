// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AIController/NormalEnemyAIController.h"

#include "NavigationSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Character/SaveMyselfEnemy.h"
#include "Enemy/FSM/NormalEnemyFSM.h"

ANormalEnemyAIController::ANormalEnemyAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SetPerceptionComponent(*PerceptionComp);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 500.f;
	SightConfig->LoseSightRadius = 600.f;
	SightConfig->PeripheralVisionAngleDegrees = 130.f;
	SightConfig->SetMaxAge(3.f);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void ANormalEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	EnemyActor = Cast<ASaveMyselfEnemy>(InPawn);

	if(PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ANormalEnemyAIController::OnTargetPerceptionUpdated);
	}
}

void ANormalEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(!Actor || !EnemyActor) return;
	if(Actor->IsA<ASaveMyselfEnemy>()) return;

	bool bIsStructure = Actor->ActorHasTag(FName("Structure"));
	bool bIsPlayer = Actor->ActorHasTag(FName("Player"));
}

void ANormalEnemyAIController::HandleIdle()
{
	if(!EnemyActor) return;

	EnemyActor->GetMovementComponent()->StopMovementImmediately();
}

void ANormalEnemyAIController::HandlePatrol()
{
	if (!EnemyActor) return;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn && LineOfSightTo(PlayerPawn))
	{
		FVector TargetLocation = PlayerPawn->GetActorLocation();

		MoveToLocation(TargetLocation);
	}
}

void ANormalEnemyAIController::HandleChase()
{
	if(!EnemyActor) return;

	UNormalEnemyFSM* EnemyComponent = EnemyActor->GetEnemyFSMComponent();

	AActor* Target = EnemyComponent->GetTargetActor();
	if(Target)
	{
		MoveToActor(Target);
	}
	else
	{
		EnemyComponent->SetMonsterState(EMonsterState::Patrol);
	}
}

void ANormalEnemyAIController::HandleAttack()
{
}

void ANormalEnemyAIController::EvaluateState()
{
	if(!EnemyActor || !PerceptionComp) return;

	UNormalEnemyFSM* EnemyComponent = EnemyActor->GetEnemyFSMComponent();

	TArray<AActor*> PerceivedActors;
	PerceptionComp->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);

	AActor* ClosestTarget = nullptr;
	float MinDistance = FLT_MAX;

	for(AActor* Actor : PerceivedActors)
	{
		if(Actor->IsA<ASaveMyselfEnemy>()) continue;

		if(!Actor->ActorHasTag(FName("Structure")) && !Actor->ActorHasTag(FName("Player"))) continue;

		float Dist = FVector::Dist(Actor->GetActorLocation(), EnemyActor->GetActorLocation());
		if(Dist < MinDistance)
		{
			MinDistance = Dist;
			ClosestTarget = Actor;
		}
	}

	if(ClosestTarget)
	{
		EnemyComponent->SetTargetActor(ClosestTarget);
		if(MinDistance <= EnemyComponent->GetAttackRange())
		{
			EnemyComponent->SetMonsterState(EMonsterState::Attack);
		}
		else
		{
			EnemyComponent->SetMonsterState(EMonsterState::Chase);
		}
	}
	else
	{
		EnemyComponent->SetMonsterState(EMonsterState::Patrol);	
	}
}
