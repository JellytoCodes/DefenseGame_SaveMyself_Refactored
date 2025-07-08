
#include "Enemy/FSM/NormalEnemyFSM.h"
#include "NavigationInvokerComponent.h"
#include "Character/SaveMyselfEnemy.h"
#include "Engine/Engine.h"

#include "Enemy/AIController/NormalEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


UNormalEnemyFSM::UNormalEnemyFSM()
{
	PrimaryComponentTick.bCanEverTick = true;

	NavInvoker = CreateDefaultSubobject<UNavigationInvokerComponent>(TEXT("NavInvoker"));
}
void UNormalEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyInfoTable) InitializeEnemyInfo();

	SetMonsterState(EMonsterState::Patrol);
}

void UNormalEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bCanEvaluateState)
	{
		if (ASaveMyselfEnemy* OwnerPawn = Cast<ASaveMyselfEnemy>(GetOwner()))
		{
		    if (ANormalEnemyAIController* AICon = Cast<ANormalEnemyAIController>(OwnerPawn->GetController()))
		    {
		        AICon->EvaluateState();
		    }
		}
	}
}

void UNormalEnemyFSM::EquipWeapon()
{

}

void UNormalEnemyFSM::OnEnterIdle()
{
	if (ASaveMyselfEnemy* OwnerPawn = Cast<ASaveMyselfEnemy>(GetOwner()))
	{
	    if (ANormalEnemyAIController* AICon = Cast<ANormalEnemyAIController>(OwnerPawn->GetController()))
	    {
	        AICon->HandleIdle();
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("Try Idle")));
	    }
	}
}

void UNormalEnemyFSM::OnEnterPatrol()
{
	if (ASaveMyselfEnemy* OwnerPawn = Cast<ASaveMyselfEnemy>(GetOwner()))
	{
	    if (ANormalEnemyAIController* AICon = Cast<ANormalEnemyAIController>(OwnerPawn->GetController()))
	    {
	        AICon->HandlePatrol();
	    }
	}
}

void UNormalEnemyFSM::OnEnterChase()
{
	if (ASaveMyselfEnemy* OwnerPawn = Cast<ASaveMyselfEnemy>(GetOwner()))
	{
	    if (ANormalEnemyAIController* AICon = Cast<ANormalEnemyAIController>(OwnerPawn->GetController()))
	    {
	        AICon->HandleChase();
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("Try Chase")));
	    }
	}
}

void UNormalEnemyFSM::OnEnterAttack()
{
	bCanEvaluateState = false;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("Try Attack")));
}

void UNormalEnemyFSM::OnEnterDamage()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("Try Damaged")));
}

void UNormalEnemyFSM::OnEnterDead()
{

}

void UNormalEnemyFSM::SetMonsterState(EMonsterState NewState)
{
	//if(bIsDeath) return;

	curState = NewState;

	switch(NewState)
	{
		case EMonsterState::Idle :
			OnEnterIdle();
		break;

		case EMonsterState::Patrol :
			OnEnterPatrol();
		break;

		case EMonsterState::Chase :
			OnEnterChase();
		break;

		case EMonsterState::Attack :
			OnEnterAttack();
		break;

		case EMonsterState::Damage :
			OnEnterDamage();
		break;

		case EMonsterState::Dead:
			OnEnterDead();
		break;
	}
}

void UNormalEnemyFSM::InitializeEnemyInfo()
{
	if (ASaveMyselfEnemy* OwnerPawn = Cast<ASaveMyselfEnemy>(GetOwner()))
	{
		FName EnemyName = OwnerPawn->Tags[1];
		if (auto* FindEnemyData = EnemyInfoTable->FindRow<FEnemyInformation>(EnemyName, TEXT("")))
		{
			EnemyInformation.EnemyName = FindEnemyData->EnemyName;
			EnemyInformation.EnemyType = FindEnemyData->EnemyType;
			EnemyInformation.EliteType = FindEnemyData->EliteType;
			EnemyInformation.MaxHP = FindEnemyData->MaxHP;
			EnemyInformation.MoveSpeed = FindEnemyData->MoveSpeed;
			EnemyInformation.AttackPower = FindEnemyData->AttackPower;
			EnemyInformation.AttackInterval = FindEnemyData->AttackInterval;
			EnemyInformation.AttackRange = FindEnemyData->AttackRange;

			UE_LOG(LogTemp, Warning, TEXT("Monster Name [%s]"), *EnemyInformation.EnemyName.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Monster Type [%d]"), EnemyInformation.EnemyType);
			UE_LOG(LogTemp, Warning, TEXT("EliteAIType [%d]"), EnemyInformation.EliteType);
			UE_LOG(LogTemp, Warning, TEXT("MaxHP [%.2f]"), EnemyInformation.MaxHP);

			OwnerPawn->GetCharacterMovement()->MaxWalkSpeed = EnemyInformation.MoveSpeed;
		}
	}
}
