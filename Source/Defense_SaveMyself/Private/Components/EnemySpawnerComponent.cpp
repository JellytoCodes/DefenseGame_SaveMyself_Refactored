// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnemySpawnerComponent.h"

#include "Actor/SpawnActor.h"
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
				DurationTypeSpawned();
			}
			if (SpawnType == ESpawnType::Infinite)
			{
				InfiniteTypeSpawned();
			}
		});
	}
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

void UEnemySpawnerComponent::DurationTypeSpawned()
{
	GetWorld()->GetTimerManager().SetTimer(DurationTimerHandle, [this]()
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ASaveMyselfEnemy>(SpawnEnemies[SpawnCount].SpawnEnemy, GetSpawnLocation(), FRotator::ZeroRotator, SpawnParams);

		if (++SpawnCount == SpawnEnemies.Num())
		{
			GetWorld()->GetTimerManager().ClearTimer(DurationTimerHandle);
			if (ASpawnActor* SpawnActor = Cast<ASpawnActor>(GetOwner()))
			{
				SpawnActor->SpawnerDestroy();
			}
		}
	}, SpawnEnemies[SpawnCount].SpawnDelay, true);
}

void UEnemySpawnerComponent::InfiniteTypeSpawned()
{
	int32 Index = 0;
	int32 EnemyInfiniteDelay = 1;

	GetWorld()->GetTimerManager().SetTimer(InfiniteTimerHandle,[&]()
	{
		Index = FMath::RandRange(0, SpawnEnemies.Num() - 1);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ASaveMyselfEnemy>(SpawnEnemies[Index].SpawnEnemy, GetSpawnLocation(), FRotator::ZeroRotator, SpawnParams);
		EnemyInfiniteDelay+=2;
	}, SpawnEnemies[Index].SpawnDelay * EnemyInfiniteDelay, true);	
}

