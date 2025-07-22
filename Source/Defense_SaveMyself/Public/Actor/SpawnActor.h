#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

class UEnemySpawnerComponent;

UCLASS()
class DEFENSE_SAVEMYSELF_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnActor();

	void SpawnerDestroy();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UEnemySpawnerComponent> EnemySpawnerComponent;
};
