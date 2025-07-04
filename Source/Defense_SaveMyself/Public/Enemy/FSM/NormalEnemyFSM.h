#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NormalEnemyFSM.generated.h"

class UNavigationInvokerComponent;
class USoundBase;
class UAudioComponent;

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
    Idle,		//��� ����
    Patrol,		//��ǥ ����(�ʳ�) �̵�
    Chase,		//�÷��̾�, ������ ��� ����
    Attack,		//��� ����
    Damage,		//�ǰ� ����
    Dead,		//��� ó��
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

	float GetAttackRange() const { return AttackRange;}

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

	float MaxHP;
	float CurHP;
	float MoveSpeed;
	float AttackPower;
	float AttackElapsedTime;
	float AttackInterval;
	float AttackRange;
	//EMonsterType monsterType;
	//EEliteAIType eliteAIType;
	TObjectPtr<UStaticMesh> WeaponMesh;

	void InitializeEnemyData();
	void EquipWeapon();
	//virtual void ReceiveDamage_Implementation(float Damage) override;

	virtual void OnEnterIdle();
	virtual void OnEnterPatrol();
	virtual void OnEnterChase();
	virtual void OnEnterAttack();
	virtual void OnEnterDamage();
	virtual void OnEnterDead();

	//State ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	bool bIsDeath = false;

	void Dead();

	bool bCanEvaluateState = true;
};
