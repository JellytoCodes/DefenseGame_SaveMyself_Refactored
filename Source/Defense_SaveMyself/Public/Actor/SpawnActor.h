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

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UEnemySpawnerComponent* EnemySpawnerComponent;

};
