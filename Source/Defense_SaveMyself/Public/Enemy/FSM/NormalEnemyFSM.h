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

	FEnemyInformation EnemyInformation;
	float CurrentHp = 0.f;

protected : 
	virtual void BeginPlay() override;

	UPROPERTY()
	AActor* TargetActor;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* EnemyInfoTable;

	void InitializeEnemyInfo();
	void EquipWeapon();
};
