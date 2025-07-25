#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interact/CombatInterface.h"
#include "SaveMyselfCharacterBase.generated.h"

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfCharacterBase : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	ASaveMyselfCharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeCharacterInfo();

	virtual void Die();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> DeathAnim;

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;

	UPROPERTY(BlueprintReadOnly)
	bool bIsHitReact;
};
