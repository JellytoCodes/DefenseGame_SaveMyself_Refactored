// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StageManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class DEFENSE_SAVEMYSELF_API UStageManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStageManagerComponent();

protected:
	virtual void BeginPlay() override;

};
