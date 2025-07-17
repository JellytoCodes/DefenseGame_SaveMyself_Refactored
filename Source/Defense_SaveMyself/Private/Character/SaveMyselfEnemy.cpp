
#include "Character/SaveMyselfEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy/AIController/NormalEnemyAIController.h"
#include "Enemy/FSM/NormalEnemyFSM.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetComponents/EffectWidgetComponent.h"

ASaveMyselfEnemy::ASaveMyselfEnemy()
{
	EnemyComponent = CreateDefaultSubobject<UNormalEnemyFSM>("EnemyFSMComponent");
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

void ASaveMyselfEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (EffectWidgetComponentClass)
	{
		EffectWidgetComponent = NewObject<UEffectWidgetComponent>(this, EffectWidgetComponentClass);
		EffectWidgetComponent->RegisterComponent();
		EffectWidgetComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		EffectWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	}
}

void ASaveMyselfEnemy::BindingEvent_Implementation(const float CurEffect)
{
	if (EnemyAIController->GetBlackboardComponent()->GetValueAsBool(FName("bIsBinding"))) return;

	FTimerHandle BindingTime;
	EnemyAIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsBinding"), true);
	EffectWidgetComponent->BindingEvent(true);
	GetWorldTimerManager().SetTimer(BindingTime, [this]
	{
		EnemyAIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsBinding"), false);
		EffectWidgetComponent->BindingEvent(false);
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
