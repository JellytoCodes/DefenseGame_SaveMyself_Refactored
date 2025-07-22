
#include "Character/SaveMyselfEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/SaveMyselfCharacter.h"
#include "Enemy/AIController/NormalEnemyAIController.h"
#include "Enemy/FSM/NormalEnemyFSM.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetComponents/EffectWidgetComponent.h"
#include "Components/CapsuleComponent.h"

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
	BlackboardInitialize();
}

void ASaveMyselfEnemy::BindingEvent_Implementation(const float CurEffect)
{
	if (EnemyAIController->GetBlackboardComponent()->GetValueAsBool(FName("bIsBinding"))) return;

	EnemyAIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsBinding"), true);
	EffectWidgetComponent->BindEventDelegate.Broadcast(true);
	GetWorldTimerManager().SetTimer(BindingTime, [this]
	{
		EnemyAIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsBinding"), false);
		EffectWidgetComponent->BindEventDelegate.Broadcast(false);
	}, CurEffect, false);
}

void ASaveMyselfEnemy::DamagedEvent_Implementation(const float Damage)
{
	EnemyComponent->CurrentHp -= Damage;
	UpdateHPProgressBar();
	if (EnemyComponent->CurrentHp <= 0)
	{
		Die();
	}
}

void ASaveMyselfEnemy::DotDamagedEvent_Implementation(const float Damage)
{
	EffectWidgetComponent->DotEventDelegate.Broadcast(true);
	GetWorldTimerManager().SetTimer(SlowMovementTime, [this, Damage]
	{
		EnemyComponent->CurrentHp -= Damage;
		UpdateHPProgressBar();
		EffectWidgetComponent->DotEventDelegate.Broadcast(false);
		if (EnemyComponent->CurrentHp <= 0)
		{
			Die();
		}
	}, 1.f, true);
}

void ASaveMyselfEnemy::SlowMovementEvent_Implementation(const float CurEffect)
{
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / 2;
	EffectWidgetComponent->SlowMovementEventDelegate.Broadcast(true);
	GetWorldTimerManager().SetTimer(SlowMovementTime, [this]
	{
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * 2;
		EffectWidgetComponent->SlowMovementEventDelegate.Broadcast(false);
	}, CurEffect, false);
}

void ASaveMyselfEnemy::Die()
{
	EnemyAIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsDied"), true);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorldTimerManager().ClearTimer(BindingTime);
	GetWorldTimerManager().ClearTimer(DotDamageTime);
	GetWorldTimerManager().ClearTimer(SlowMovementTime);
	SetLifeSpan(2.f);
}

void ASaveMyselfEnemy::BlackboardInitialize() const
{
	if (EnemyAIController)
	{
		EnemyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		EnemyAIController->RunBehaviorTree(BehaviorTree);

		EnemyAIController->GetBlackboardComponent()->SetValueAsFloat(FName("AttackPower"),EnemyComponent->EnemyInformation.AttackPower);
		EnemyAIController->GetBlackboardComponent()->SetValueAsFloat(FName("AttackInterval"),EnemyComponent->EnemyInformation.AttackInterval);
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (APawn* PlayerPawn = PC->GetPawn())
			{
				if (ASaveMyselfCharacter* PlayerCharacter = Cast<ASaveMyselfCharacter>(PlayerPawn))
				{
					EnemyAIController->GetBlackboardComponent()->SetValueAsObject(FName("PlayerActor"), PlayerCharacter);
					PlayerCharacter->OnStageDefeatDelegate.AddDynamic(this, &ASaveMyselfEnemy::SetIsPlayerState);
					PlayerCharacter->OnStageVictoryDelegate.AddDynamic(this, &ASaveMyselfEnemy::SetIsPlayerState);
				}
			}
		}
	}
}

void ASaveMyselfEnemy::SetIsPlayerState()
{
	if (EnemyAIController)
	{
		EnemyAIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsStageVictoryOrDefeat"), true);
	}
	GetWorldTimerManager().ClearTimer(BindingTime);
	GetWorldTimerManager().ClearTimer(DotDamageTime);
	GetWorldTimerManager().ClearTimer(SlowMovementTime);
}
