#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EffectWidgetComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectEventSignature, bool, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEffectDamageEventSignature, bool, State, float, Damage);

UCLASS()
class DEFENSE_SAVEMYSELF_API UEffectWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public :
	UPROPERTY(BlueprintAssignable)
	FOnEffectEventSignature BindEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEffectDamageEventSignature ExplosiveEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEffectEventSignature SlowMovementEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEffectDamageEventSignature DotEventDelegate;
};
