// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySpawnerComponent.generated.h"

UENUM(BlueprintType)
enum class ESpawnType : uint8
{
	Duration,
	Infinite,
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FVector GetSpawnLocation() const;
	void DurationTypeSpawned(int32 Index);
	void InfiniteTypeSpawned();

	int SpawnCount = 0;

	FTimerHandle InfiniteTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	float SpawnSpread = 90.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	int32 SpawnPoint = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	float MinSpawnDistance = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	float MaxSpawnDistance = 400.f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnDuration = 2.f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TArray<TSubclassOf<ASaveMyselfEnemy>> SpawnEnemies;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	ESpawnType SpawnType = ESpawnType::Duration;
};
