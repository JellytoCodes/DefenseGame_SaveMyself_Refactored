
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SaveMyselfEnemyInfo.generated.h"

class ASaveMyselfEnemy;
class UStaticMesh;

UENUM(BlueprintType)
enum class EMonsterType : uint8
{
	Normal,
	Elite,
};

UENUM(BlueprintType)
enum class EEliteAIType : uint8
{
	None,
	Destroyer,
	Mage,
};

USTRUCT(BlueprintType)
struct FEnemyInformation : public FTableRowBase
{
	GENERATED_BODY()

	FEnemyInformation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
	FName EnemyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
	EMonsterType EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
	EEliteAIType EliteType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
	float AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
	float AttackInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
	float AttackRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
	UStaticMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Info")
	TSubclassOf<ASaveMyselfEnemy> EnemyClass;
};