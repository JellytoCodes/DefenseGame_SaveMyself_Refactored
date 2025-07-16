
#include "Character/SaveMyselfEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy/AIController/NormalEnemyAIController.h"
#include "Enemy/FSM/NormalEnemyFSM.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASaveMyselfEnemy::ASaveMyselfEnemy()
{
	EnemyComponent = CreateDefaultSubobject<UNormalEnemyFSM>(TEXT("EnemyFSMComponent"));
}

UNormalEnemyFSM* ASaveMyselfEnemy::GetEnemyFSMComponent()
{
	return EnemyComponent;
}

void ASaveMyselfEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	EnemyAIController = Cast<ANormalEnemyAIController>(NewController);
	if (EnemyAIController)
	{
		EnemyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		EnemyAIController->RunBehaviorTree(BehaviorTree);
		
		EnemyAIController->GetBlackboardComponent()->SetValueAsFloat(FName("TargetDistance"), EnemyComponent->GetAttackRange());
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (APawn* PlayerPawn = PC->GetPawn())
			{
				if (PlayerPawn->ActorHasTag(FName("Player")))
				{
					EnemyAIController->GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), PlayerPawn); 			
				}
			}
		}
	}
}

void ASaveMyselfEnemy::BindingEvent_Implementation(const float CurEffect)
{
	FTimerHandle BindingTime;
	GetCharacterMovement()->MaxWalkSpeed = 0;
	GetWorldTimerManager().SetTimer(BindingTime, [this]
	{
		GetCharacterMovement()->MaxWalkSpeed = EnemyComponent->EnemyInformation.MoveSpeed;	
	}, CurEffect, false);
}

void ASaveMyselfEnemy::DamagedEvent_Implementation(const float Damage)
{
	EnemyComponent->CurrentHp -= Damage;
	if (EnemyComponent->CurrentHp <= 0)
	{
		Die();
	}
}

void ASaveMyselfEnemy::Die()
{
	if (DeathAnim) PlayAnimMontage(DeathAnim);

	//Super::Die();
}
