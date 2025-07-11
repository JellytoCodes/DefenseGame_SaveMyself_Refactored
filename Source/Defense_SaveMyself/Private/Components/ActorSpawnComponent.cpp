#include "Components/ActorSpawnComponent.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"
#include "Actor/SaveMyselfActor.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"

UActorSpawnComponent::UActorSpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UActorSpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	if (auto* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
	{
		ItemSubsystem->ExportItemDataDelegate.AddDynamic(this, &UActorSpawnComponent::GetSpawnItemData);
	}
}

void UActorSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PreviewActor)
	{
		FHitResult HitResult;
		if (TraceToGround(HitResult))
		{
			//GridSnap
			float SnappedX = FMath::GridSnap(HitResult.ImpactPoint.X, GridSize);
			float SnappedY = FMath::GridSnap(HitResult.ImpactPoint.Y, GridSize);
		
			FVector ConfirmLocation(SnappedX, SnappedY, HitResult.ImpactPoint.Z);

			PreviewActor->SetActorLocation(ConfirmLocation);
			PreviewActor->SetActorRotation(FRotator::ZeroRotator);
			SetGhostMaterial(true);
		}
		else
		{
			SetGhostMaterial(false);
		}
	}
}

void UActorSpawnComponent::GetSpawnItemData(const FItemInformation& ItemData)
{
	SpawnItemData = ItemData;
	if (SpawnItemData.ItemType == EItemTypes::Weapon) return;

	CreatePreviewActor();
}

void UActorSpawnComponent::CreatePreviewActor()
{
	if (PreviewActor)
	{
		PreviewActor->Destroy();
		PreviewActor = nullptr;
	}

	if (!SpawnItemData.ItemClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	PreviewActor = GetWorld()->SpawnActor<AActor>(SpawnItemData.ItemClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (PreviewActor)
	{
		PreviewActor->SetActorEnableCollision(false);
	}
}

void UActorSpawnComponent::SetGhostMaterial(bool bCanPlace)
{
	if (!PreviewActor) return;

	TArray<UMeshComponent*> MeshComponents;
	PreviewActor->GetComponents<UMeshComponent>(MeshComponents);

	for (auto* Mesh : MeshComponents)
	{
		if (Mesh)
		{
			Mesh->SetMaterial(0, bCanPlace ? CanPlaceMaterial : CannotPlaceMaterial);
		}
	}
}

bool UActorSpawnComponent::TraceToGround(FHitResult& HitResult) const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return false;

	return PC->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, HitResult);
}

void UActorSpawnComponent::ConfirmPlacement()
{
	if (!PreviewActor) return;

	PreviewActor->SetActorEnableCollision(true);
	PreviewActor = nullptr;

	// 여기에서 Subsystem 호출하여 수량 감소 요청할 수 있음
}