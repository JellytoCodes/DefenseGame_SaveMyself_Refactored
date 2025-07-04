// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SaveMyselfEnemy.h"
#include "Enemy/FSM/NormalEnemyFSM.h"

ASaveMyselfEnemy::ASaveMyselfEnemy()
{
	EnemyComponent = CreateDefaultSubobject<UNormalEnemyFSM>(TEXT("EnemyFSMComponent"));
}

UNormalEnemyFSM* ASaveMyselfEnemy::GetEnemyFSMComponent()
{
	return EnemyComponent;
}
