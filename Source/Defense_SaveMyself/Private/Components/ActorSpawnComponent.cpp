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

			bCanPlaceConfirm = true;
			SetGhostMaterial(bCanPlaceConfirm);
		}
		else
		{
			bCanPlaceConfirm = false;
			SetGhostMaterial(bCanPlaceConfirm);
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

	return PC->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false, HitResult);
}

void UActorSpawnComponent::ConfirmPlacement()
{
	if (SpawnItemData.ItemType == EItemTypes::Weapon)
	{
		FVector Location = GetOwner()->GetActorLocation();
		FRotator Rotation = GetOwner()->GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AActor* ProjectileActor = GetWorld()->SpawnActor<AActor>(SpawnItemData.ItemClass, Location, Rotation, SpawnParams);

		ConfirmActorSpawnDelegate.Broadcast(SpawnItemData);

		ProjectileActor->SetLifeSpan(5.f);
	}

	else
	{
		if (!PreviewActor) return;

		FVector Location = PreviewActor->GetActorLocation();
		FRotator Rotation = PreviewActor->GetActorRotation();

		PreviewActor->Destroy();
		PreviewActor = nullptr;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AActor* PlacedActor = GetWorld()->SpawnActor<AActor>(SpawnItemData.ItemClass, Location, Rotation, SpawnParams);

		if (PlacedActor)
		{
			PlacedActor->SetActorEnableCollision(true);
		}

		ConfirmActorSpawnDelegate.Broadcast(SpawnItemData);
		SpawnItemData = FItemInformation();
	}
}