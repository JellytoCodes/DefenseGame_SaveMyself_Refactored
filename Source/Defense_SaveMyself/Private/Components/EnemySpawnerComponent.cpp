// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnemySpawnerComponent.h"

#include "Character/SaveMyselfEnemy.h"
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"

UEnemySpawnerComponent::UEnemySpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UEnemySpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (auto* StageSubsystem = USaveMyselfStageSubsystem::GetStageSubsystem(this))
	{
		StageSubsystem->OnActionPhaseDelegate.AddLambda([&]()
		{
			if (SpawnType == ESpawnType::Duration)
			{
				for (int32 i = 0 ; i < SpawnEnemies.Num() ; i++)
				{
					DurationTypeSpawned(i);
				}
			}
			else if (SpawnType == ESpawnType::Infinite)
			{
				InfiniteTypeSpawned();
			}
		});
	}
}

void UEnemySpawnerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (InfiniteTimerHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(InfiniteTimerHandle);
}

FVector UEnemySpawnerComponent::GetSpawnLocation() const
{
	const AActor* EnemySpawner = GetOwner();
	if (!EnemySpawner) return FVector::ZeroVector;

	const FVector Location = EnemySpawner->GetActorLocation();
	const FVector Right = EnemySpawner->GetActorForwardVector();

	const float HalfSpread = SpawnSpread / 2.f;
	const float OffsetX = FMath::FRandRange(-HalfSpread, HalfSpread);

	FVector ChosenSpawnLocation = Location + Right * OffsetX;
	ChosenSpawnLocation += EnemySpawner->GetActorForwardVector() * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

	return ChosenSpawnLocation + FVector(0.f, 0.f, 100.f);
}

void UEnemySpawnerComponent::DurationTypeSpawned(int32 Index)
{
	FTimerHandle SpawnTimer;

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, [this, Index]()
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ASaveMyselfEnemy>(SpawnEnemies[Index].SpawnEnemy, GetSpawnLocation(), FRotator::ZeroRotator, SpawnParams);
	}, SpawnEnemies[Index].SpawnDelay, false);
}

void UEnemySpawnerComponent::InfiniteTypeSpawned()
{
	const int32 Index = FMath::RandRange(0, SpawnEnemies.Num() - 1);
	GetWorld()->GetTimerManager().SetTimer(InfiniteTimerHandle,[&]()
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ASaveMyselfEnemy>(SpawnEnemies[Index].SpawnEnemy, GetSpawnLocation(), FRotator::ZeroRotator, SpawnParams);
	}, SpawnEnemies[Index].SpawnDelay, true);
}

