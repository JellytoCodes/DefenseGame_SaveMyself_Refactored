
#include "Components/ActorEffectComponent.h"

#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/OverlapResult.h"

UActorEffectComponent::UActorEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UActorEffectComponent::ApplySingleDamage(AActor* TargetActor, float CurEffect)
{
	//Single Target Damaged (CurEffect)
}

void UActorEffectComponent::ApplyAOEDamage(AActor* TargetActor, float CurEffect, float EffectRadius)
{
	TArray<FOverlapResult> OverlapHits;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(EffectRadius);
	const bool bHit = GetWorld()->OverlapMultiByChannel(
	OverlapHits, TargetActor->GetActorLocation(), FQuat::Identity, ECC_Pawn, Sphere);

	if (bHit)
	{
		for (const FOverlapResult& Result : OverlapHits)
		{
			if (TargetActor)
			{
				//Target Damaged (Receive CurEffect)
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

	if (bHit)
	{
		for (const FOverlapResult& Result : OverlapHits)
		{
			if (TargetActor)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Triggered Target Actor [%s]"), *TargetActor->GetName()));
				//Target Binding (Receive CurEffect)
			}
		}
	}
}

