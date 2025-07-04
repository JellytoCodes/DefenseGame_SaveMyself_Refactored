#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SaveMyselfCharacterBase.generated.h"

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASaveMyselfCharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeCharacterInfo();
};
