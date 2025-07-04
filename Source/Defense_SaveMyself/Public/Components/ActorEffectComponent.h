// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEFENSE_SAVEMYSELF_API UActorEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActorEffectComponent();

	UFUNCTION(BlueprintCallable)
	void ApplySingleDamage(AActor* TargetActor, float CurEffect);

	UFUNCTION(BlueprintCallable)
	void ApplyAOEDamage(AActor* TargetActor, float CurEffect, float EffectRadius);

	UFUNCTION(BlueprintCallable)
	void ApplyBind(AActor* TargetActor, float CurEffect, float EffectRadius);
};