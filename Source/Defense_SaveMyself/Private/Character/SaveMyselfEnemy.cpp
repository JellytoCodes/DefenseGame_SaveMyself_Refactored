
#include "Character/SaveMyselfEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy/AIController/NormalEnemyAIController.h"
#include "Enemy/FSM/NormalEnemyFSM.h"
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
