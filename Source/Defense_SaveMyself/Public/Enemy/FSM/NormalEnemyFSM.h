#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/SaveMyselfEnemyInfo.h"
#include "NormalEnemyFSM.generated.h"

class UNavigationInvokerComponent;
class USoundBase;
class UAudioComponent;

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
    Idle,		//대기 상태
    Patrol,		//목표 지점 이동
    Chase,		//플레이어, 구조물 추적
    Attack,		//대상 공격
    Damage,		//피격 반응
    Dead,		//사망 처리
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEFENSE_SAVEMYSELF_API UNormalEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNormalEnemyFSM();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE void SetTargetActor(AActor* NewTarget) { TargetActor = NewTarget; }
	FORCEINLINE AActor* GetTargetActor() const { return TargetActor; }

	void SetMonsterState(EMonsterState NewState); 
	EMonsterState GetMonsterState() const { return curState; }

	float GetAttackRange() const { return EnemyInformation.AttackRange;}

protected : 
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MonsterState")
	EMonsterState curState = EMonsterState::Patrol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MonsterID")
	FName MonsterID;	

	UPROPERTY()
	AActor* TargetActor;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Nav")
	TObjectPtr<UNavigationInvokerComponent> NavInvoker;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> DeadSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> AttackSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<UAudioComponent> SoundOutComp;

	UPROPERTY(EditDefaultsOnly, Category = "Data Table")
	TObjectPtr<UDataTable> EnemyInfoTable;

	FEnemyInformation EnemyInformation;

	void InitializeEnemyInfo();
	void EquipWeapon();
	//virtual void ReceiveDamage_Implementation(float Damage) override;

	void OnEnterIdle();
	void OnEnterPatrol();
	void OnEnterChase();
	void OnEnterAttack();
	void OnEnterDamage();
	void OnEnterDead();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	bool bIsDeath = false;

	void Dead();

	bool bCanEvaluateState = true;
};
