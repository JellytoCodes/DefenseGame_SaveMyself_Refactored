#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/SaveMyselfEnemyInfo.h"
#include "NormalEnemyFSM.generated.h"

class UDataTable;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEFENSE_SAVEMYSELF_API UNormalEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNormalEnemyFSM();

	float GetAttackRange() const { return EnemyInformation.AttackRange;}

protected : 
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MonsterID")
	FName MonsterID;	

	UPROPERTY()
	AActor* TargetActor;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* EnemyInfoTable;

	FEnemyInformation EnemyInformation;

	void InitializeEnemyInfo();
	void EquipWeapon();
};
