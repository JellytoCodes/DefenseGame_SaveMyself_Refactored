#pragma once

#include "CoreMinimal.h"
#include "Character/SaveMyselfCharacterBase.h"
#include "SaveMyselfCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageResultSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLifeDelegate, int32, InHP);
class UActorSpawnComponent;

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfCharacter : public ASaveMyselfCharacterBase
{
	GENERATED_BODY()

public :
	ASaveMyselfCharacter();

	/* Combat Interface */
	virtual void DamagedEvent_Implementation(const float Damage) override;
	/* End Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnStageResultSignature OnStageDefeatDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerLifeDelegate PlayerLifeDelegate;
protected :
	virtual void BeginPlay() override;
	virtual void InitializeCharacterInfo() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnActorComponent")
	TObjectPtr<UActorSpawnComponent> ActorSpawnComponent;

private :
	int32 PlayerHP = 5;
};
