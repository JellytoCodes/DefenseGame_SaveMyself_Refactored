#pragma once

#include "CoreMinimal.h"
#include "Character/SaveMyselfCharacterBase.h"
#include "SaveMyselfCharacter.generated.h"

class UActorSpawnComponent;
class UConfirmPlacedWidgetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageResultSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLifeDelegate, int32, InHP);

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
	FOnStageResultSignature OnStageVictoryDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerLifeDelegate PlayerLifeDelegate;

protected :
	virtual void BeginPlay() override;
	virtual void InitializeCharacterInfo() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SpawnActorComponent")
	TObjectPtr<UActorSpawnComponent> ActorSpawnComponent;

	UPROPERTY(EditDefaultsOnly, Category = "ConfirmWidgetComponent")
	TSubclassOf<UConfirmPlacedWidgetComponent> ConfirmPlacedWidgetComponentClass;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ConfirmWidgetComponent")
	TObjectPtr<UConfirmPlacedWidgetComponent> ConfirmPlacedWidgetComponent;

	void OnStageDefeatBroadCast() const;
	void OnStageVictoryBroadCast() const;

private :
	int32 PlayerHP = 5;
};
