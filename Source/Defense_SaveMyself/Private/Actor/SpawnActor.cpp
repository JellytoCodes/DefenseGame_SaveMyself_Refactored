
#include "Actor/SpawnActor.h"

#include "Components/EnemySpawnerComponent.h"

ASpawnActor::ASpawnActor()
{
	PrimaryActorTick.bCanEverTick = false;

	EnemySpawnerComponent = CreateDefaultSubobject<UEnemySpawnerComponent>("EnemySpawnerComponent");
}

void ASpawnActor::SpawnerDestroy()
{
	Destroy();
}


