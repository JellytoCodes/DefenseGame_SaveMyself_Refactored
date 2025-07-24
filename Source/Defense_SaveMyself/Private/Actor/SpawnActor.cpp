#include "Actor/SpawnActor.h"

#include "Components/EnemySpawnerComponent.h"
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"

ASpawnActor::ASpawnActor()
{
	PrimaryActorTick.bCanEverTick = false;

	EnemySpawnerComponent = CreateDefaultSubobject<UEnemySpawnerComponent>("EnemySpawnerComponent");
}

void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();

}

void ASpawnActor::Destroyed()
{
	Super::Destroyed();

	if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
	{
		if (StageSubsystem->GetStageQuestType() == EStageQuestType::TargetDestroy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString("Target Destroy"));
			StageSubsystem->NotifyActorDestroyed(this);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString("Target Destroy But Not TargetDestroy Mission"));
		}
	}
}
