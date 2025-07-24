#pragma once

#include "CoreMinimal.h"
#include "Character/SaveMyselfCharacterBase.h"
#include "SaveMyselfCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageResultSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLifeDelegate, int32, InHP);

class UActorSpawnComponent;
class UConfirmPlacedWidget;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnActorComponent")
	TObjectPtr<UActorSpawnComponent> ActorSpawnComponent;

	UPROPERTY(EditDefaultsOnly, Category = "ConfirmWidgetComponent")
	TSubclassOf<UConfirmPlacedWidget> ConfirmPlacedWidgetComponentClass;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ConfirmWidgetComponent")
	TObjectPtr<UConfirmPlacedWidget> ConfirmPlacedWidgetComponent;

	void OnStageDefeatBroadCast() const;
	void OnStageVictoryBroadCast() const;

private :
	int32 PlayerHP = 5;
};
