#include "Data/SaveMyselfEnemyInfo.h"

FEnemyInformation::FEnemyInformation() :
EnemyName(NAME_None), EnemyType(EMonsterType::Normal), EliteType(EEliteAIType::None),
MaxHP(0), MoveSpeed(0), AttackPower(0), AttackInterval(0), AttackRange(0), WeaponMesh(nullptr), EnemyClass(nullptr)
{

}
