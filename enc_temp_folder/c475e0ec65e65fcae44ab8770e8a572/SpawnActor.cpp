#include "Actor/SpawnActor.h"

#include "Components/EnemySpawnerComponent.h"
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"

ASpawnActor::ASpawnActor()
{
	PrimaryActorTick.bCanEverTick = false;

	EnemySpawnerComponent = CreateDefaultSubobject<UEnemySpawnerComponent>("EnemySpawnerComponent");
	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(SpawnerMesh);
}

void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = TargetHP;
	PreparePhaseCollisionSet();

	if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
	{
		if (bIsTargetingMode) StageSubsystem->OnActionPhaseDelegate.AddUObject(this, &ASpawnActor::ActionPhaseCollisionSet);
	}
}

void ASpawnActor::Destroyed()
{
	Super::Destroyed();

	if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
	{
		if (StageSubsystem->GetStageQuestType() == EStageQuestType::TargetDestroy)
		{
			StageSubsystem->NotifyActorDestroyed(this);
		}
	}
	EnemySpawnerComponent->ClearTimer();
}

void ASpawnActor::DamagedEvent_Implementation(const float Damage)
{
	CurrentHP -= Damage;
	if (CurrentHP <= 0)
	{
		Destroy();
	}
}

void ASpawnActor::PreparePhaseCollisionSet() const
{
	SpawnerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASpawnActor::ActionPhaseCollisionSet() const
{
	SpawnerMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
