#pragma once

#include "CoreMinimal.h"
#include "Character/SaveMyselfCharacterBase.h"
#include "SaveMyselfCharacter.generated.h"

class UActorSpawnComponent;

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfCharacter : public ASaveMyselfCharacterBase
{
	GENERATED_BODY()

public :
	ASaveMyselfCharacter();

protected :
	virtual void BeginPlay() override;
	virtual void InitializeCharacterInfo() override;

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnActorComponent", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UActorSpawnComponent> ActorSpawnComponent;
};
