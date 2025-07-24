#include "Components/EnemySpawnerComponent.h"
#include "Character/SaveMyselfCharacter.h"
#include "Character/SaveMyselfEnemy.h"
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SaveMyselfPlayerController.h"

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
	
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (ASaveMyselfPlayerController* SaveMyselfPC = Cast<ASaveMyselfPlayerController>(PC))
		{
			if (ASaveMyselfCharacter* SaveMyselfPlayer = Cast<ASaveMyselfCharacter>(PC->GetPawn()))
			{
				SaveMyselfPlayer->OnStageDefeatDelegate.AddDynamic(this, &UEnemySpawnerComponent::ClearTimer);
				SaveMyselfPlayer->OnStageVictoryDelegate.AddDynamic(this, &UEnemySpawnerComponent::ClearTimer);
			}
		}
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
	GetWorld()->GetTimerManager().SetTimer(DurationTimerHandle, [&]()
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ASaveMyselfEnemy>(SpawnEnemies[SpawnCount].SpawnEnemy, GetSpawnLocation(), FRotator::ZeroRotator, SpawnParams);

		if (++SpawnCount == SpawnEnemies.Num())
		{
			ClearTimer();
		}
	}, SpawnDelay, true);
}

void UEnemySpawnerComponent::InfiniteTypeSpawned()
{
	GetWorld()->GetTimerManager().SetTimer(InfiniteTimerHandle,[&]()
	{
		int32 Index = FMath::RandRange(0, SpawnEnemies.Num() - 1);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ASaveMyselfEnemy>(SpawnEnemies[Index].SpawnEnemy, GetSpawnLocation(), FRotator::ZeroRotator, SpawnParams);
	}, SpawnDelay, true);	
}

void UEnemySpawnerComponent::ClearTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(DurationTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(InfiniteTimerHandle);
}
