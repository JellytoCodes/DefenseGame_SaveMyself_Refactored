
#include "Enemy/FSM/NormalEnemyFSM.h"
#include "Character/SaveMyselfEnemy.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"

UNormalEnemyFSM::UNormalEnemyFSM()
{
	PrimaryComponentTick.bCanEverTick = false;

}
void UNormalEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyInfoTable) InitializeEnemyInfo();
}


void UNormalEnemyFSM::EquipWeapon()
{

}

void UNormalEnemyFSM::InitializeEnemyInfo()
{
	if (ASaveMyselfEnemy* OwnerPawn = Cast<ASaveMyselfEnemy>(GetOwner()))
	{
		FName EnemyName = OwnerPawn->Tags[1];
		if (auto* FindEnemyData = EnemyInfoTable->FindRow<FEnemyInformation>(EnemyName, TEXT("Not Found Enemy Data")))
		{
			EnemyInformation.EnemyName = FindEnemyData->EnemyName;
			EnemyInformation.EnemyType = FindEnemyData->EnemyType;
			EnemyInformation.EliteType = FindEnemyData->EliteType;
			EnemyInformation.MaxHP = FindEnemyData->MaxHP;
			EnemyInformation.MoveSpeed = FindEnemyData->MoveSpeed;
			EnemyInformation.AttackPower = FindEnemyData->AttackPower;
			EnemyInformation.AttackInterval = FindEnemyData->AttackInterval;
			EnemyInformation.AttackRange = FindEnemyData->AttackRange;
			CurrentHp = EnemyInformation.MaxHP;

			OwnerPawn->GetCharacterMovement()->MaxWalkSpeed = EnemyInformation.MoveSpeed;
		}
	}
}
