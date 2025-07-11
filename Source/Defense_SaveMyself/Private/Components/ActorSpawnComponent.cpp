#include "Components/ActorSpawnComponent.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"
#include "Actor/SaveMyselfActor.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Player/SaveMyselfPlayerController.h"

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

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (ASaveMyselfPlayerController* SMPController = Cast<ASaveMyselfPlayerController>(PC))
		{
			SMPController->ItemConfirmActionDelegate.AddDynamic(this, &UActorSpawnComponent::ConfirmPlacement);
		}
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
	if (SpawnItemData.ItemType == EItemTypes::Weapon || SpawnItemData.ItemType == EItemTypes::None)
	{
		if (PreviewActor)
		{
			PreviewActor->Destroy();
			PreviewActor = nullptr;
		}
		return;
	}

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
	if (SpawnItemData.ItemType == EItemTypes::Weapon)
	{
		// TODO.
		// Weapon 타입 아이템 일 경우 SpawnProjectile() 호출
		// 손에서 나가는 것으로 진행
		// AnimNotify로 위치 조정
	}
	else
	{
		if (!PreviewActor) return;

		PreviewActor->SetActorEnableCollision(true);
		PreviewActor = nullptr;

		ConfirmActorSpawnDelegate.Broadcast(SpawnItemData);
		SpawnItemData = FItemInformation();	
	}
}