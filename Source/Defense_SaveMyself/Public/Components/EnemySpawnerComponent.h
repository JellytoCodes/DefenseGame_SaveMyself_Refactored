// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySpawnerComponent.generated.h"

class ASaveMyselfEnemy;

UENUM(BlueprintType)
enum class ESpawnType : uint8
{
	Duration,
	Infinite,
};

USTRUCT(BlueprintType)
struct FEnemySpawnList
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASaveMyselfEnemy> SpawnEnemy;

	UPROPERTY(EditAnywhere)
	float SpawnDelay = 2.f;
};

class ASaveMyselfEnemy;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEFENSE_SAVEMYSELF_API UEnemySpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemySpawnerComponent();

protected:
	virtual void BeginPlay() override;

	FVector GetSpawnLocation() const;
	void DurationTypeSpawned();
	void InfiniteTypeSpawned();

	int SpawnCount = 0;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle InfiniteTimerHandle;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle DurationTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	float SpawnSpread = 90.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	int32 SpawnPoint = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	float MinSpawnDistance = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	float MaxSpawnDistance = 400.f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TArray<FEnemySpawnList> SpawnEnemies;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	ESpawnType SpawnType = ESpawnType::Duration;
};
