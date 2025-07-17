#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EffectWidgetComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectEventSignature, bool, State);

UCLASS()
class DEFENSE_SAVEMYSELF_API UEffectWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public :
	UPROPERTY(BlueprintAssignable)
	FOnEffectEventSignature BindEventDelegate;

	void BindingEvent(const bool State) const;
};
