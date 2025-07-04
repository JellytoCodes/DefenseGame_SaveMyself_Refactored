
#include "Enemy/FSM/NormalEnemyFSM.h"
#include "NavigationInvokerComponent.h"
#include "Engine/Engine.h"

#include "Enemy/AIController/NormalEnemyAIController.h"


UNormalEnemyFSM::UNormalEnemyFSM()
{
	PrimaryComponentTick.bCanEverTick = true;

	NavInvoker = CreateDefaultSubobject<UNavigationInvokerComponent>(TEXT("NavInvoker"));
}
void UNormalEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	SetMonsterState(EMonsterState::Patrol);
}

void UNormalEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bCanEvaluateState)
	{
		if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
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
	if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
	    if (ANormalEnemyAIController* AICon = Cast<ANormalEnemyAIController>(OwnerPawn->GetController()))
	    {
	        AICon->HandleIdle();
	    }
	}
}

void UNormalEnemyFSM::OnEnterPatrol()
{
	if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
	    if (ANormalEnemyAIController* AICon = Cast<ANormalEnemyAIController>(OwnerPawn->GetController()))
	    {
	        AICon->HandlePatrol();
	    }
	}
}

void UNormalEnemyFSM::OnEnterChase()
{
	if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
	    if (ANormalEnemyAIController* AICon = Cast<ANormalEnemyAIController>(OwnerPawn->GetController()))
	    {
	        AICon->HandleChase();
	    }
	}
}

void UNormalEnemyFSM::OnEnterAttack()
{
	bCanEvaluateState = false;
}

void UNormalEnemyFSM::OnEnterDamage()
{

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

void UNormalEnemyFSM::InitializeEnemyData()
{

}
