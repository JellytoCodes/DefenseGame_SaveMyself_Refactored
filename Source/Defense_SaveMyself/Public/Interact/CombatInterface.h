// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class DEFENSE_SAVEMYSELF_API ICombatInterface
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BindingEvent(const float CurEffect);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DamagedEvent(const float Damage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SlowMovementEvent(const float CurEffect);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DotDamagedEvent(const float Damage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UnDotDamagedEvent();
};
