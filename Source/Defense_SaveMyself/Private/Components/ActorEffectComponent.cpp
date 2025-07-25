#include "Components/ActorEffectComponent.h"
#include "Engine/Engine.h"
#include "Engine/OverlapResult.h"
#include "Interact/CombatInterface.h"

UActorEffectComponent::UActorEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UActorEffectComponent::ApplySingleDamage(AActor* TargetActor, float CurEffect)
{
	if (TargetActor->Implements<UCombatInterface>())
	{
		ICombatInterface::Execute_DamagedEvent(TargetActor, CurEffect);
	}
}

void UActorEffectComponent::ApplyAOEDamage(AActor* TargetActor, float CurEffect, float EffectRadius)
{
	TArray<FOverlapResult> OverlapHits;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(EffectRadius);
	const bool bHit = GetWorld()->OverlapMultiByChannel(
	OverlapHits, TargetActor->GetActorLocation(), FQuat::Identity, ECC_Pawn, Sphere);

	if (!bHit) return;
	
	for (const FOverlapResult& Result : OverlapHits)
	{
		if (AActor* HitActor = Result.GetActor())
		{
			if (HitActor->Implements<UCombatInterface>())
			{
				ICombatInterface::Execute_DamagedEvent(HitActor, CurEffect);
			}
		}
	}
}

void UActorEffectComponent::ApplyBind(AActor* TargetActor, float CurEffect, float EffectRadius)
{
	TArray<FOverlapResult> OverlapHits;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(EffectRadius);
	const bool bHit = GetWorld()->OverlapMultiByChannel(
	OverlapHits, TargetActor->GetActorLocation(), FQuat::Identity, ECC_Pawn, Sphere);

	if (!bHit) return;
	
	for (const FOverlapResult& Result : OverlapHits)
	{
		if (AActor* HitActor = Result.GetActor())
		{
			if (HitActor->Implements<UCombatInterface>())
			{
				ICombatInterface::Execute_BindingEvent(HitActor, CurEffect);
			}
		}
	}
}

void UActorEffectComponent::ApplyDotDamage(AActor* TargetActor, float CurEffect)
{
	if (TargetActor->Implements<UCombatInterface>())
	{
		ICombatInterface::Execute_DotDamagedEvent(TargetActor, CurEffect);
	}
}

void UActorEffectComponent::ApplySlowMovement(AActor* TargetActor, float CurEffect)
{
	if (TargetActor->Implements<UCombatInterface>())
	{
		ICombatInterface::Execute_SlowMovementEvent(TargetActor, CurEffect);
	}
}

