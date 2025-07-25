#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interact/CombatInterface.h"
#include "SpawnActor.generated.h"

class UEnemySpawnerComponent;

UCLASS()
class DEFENSE_SAVEMYSELF_API ASpawnActor : public AActor, public ICombatInterface
{
	GENERATED_BODY()
	
public:	
	ASpawnActor();

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	/* Combat Interface */
	virtual void DamagedEvent_Implementation(const float Damage) override;
	/* end Combat Interface */

	void PreparePhaseCollisionSet() const;
	void ActionPhaseCollisionSet() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UEnemySpawnerComponent> EnemySpawnerComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="TargetingMode")
	bool bIsTargetingMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> SpawnerMesh;

	UPROPERTY(EditDefaultsOnly)
	float TargetHP = 20;

	float CurrentHP = 0;
};
