#include "Components/ActorSpawnComponent.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"
#include "Actor/SaveMyselfActor.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Character/SaveMyselfCharacter.h"
#include "Defense_SaveMyself/Defense_SaveMyself.h"
#include "Kismet/KismetMathLibrary.h"
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
		
			FVector ConfirmLocation(SnappedX, SnappedY, HitResult. ImpactPoint.Z);

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

void UActorSpawnComponent::SetGhostMaterial(const bool bCanPlace) const
{
	if (!PreviewActor) return;

	TArray<UMeshComponent*> MeshComponents;
	PreviewActor->GetComponents<UMeshComponent>(MeshComponents);

	for (auto* Mesh : MeshComponents)
	{
		if (Mesh)
		{
			Mesh->SetMaterial(0, bCanPlace ? CanPlaceMaterial : CannotPlaceMaterial);
			Mesh->SetMaterial(1, bCanPlace ? CanPlaceMaterial : CannotPlaceMaterial);
			Mesh->SetMaterial(2, bCanPlace ? CanPlaceMaterial : CannotPlaceMaterial);
		}
	}
}

bool UActorSpawnComponent::TraceToGround(FHitResult& HitResult) const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return false;

	if (PC->GetHitResultUnderCursor(FloorActor, false, HitResult))
	{
		if (HitResult.GetActor()->ActorHasTag("Floor")) return true;
	}
	return false;
}

void UActorSpawnComponent::ConfirmPlacement()
{
	if (SpawnItemData.ItemType == EItemTypes::Weapon)
	{
		if (auto* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
		{
			if (ItemSubsystem->GetQuickSlotQuantity(SpawnItemData.ItemName) > 0) SpawnedProjectile();
			if (ItemSubsystem->GetQuickSlotQuantity(SpawnItemData.ItemName) == 0) DisableEquippedItem();
		}
	}

	else
	{
		SpawnedTrapAndStructure();
	}
}

void UActorSpawnComponent::SpawnedProjectile() const
{
	const ASaveMyselfCharacter* PlayerOwner = Cast<ASaveMyselfCharacter>(GetOwner());
	if (!PlayerOwner) return;

	const FVector Location = PlayerOwner->GetMesh()->GetSocketLocation(FName("armRightSocket"));

	FHitResult HitResult;
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC || !PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult)) return;

	const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Location, HitResult.ImpactPoint);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* ProjectileActor = GetWorld()->SpawnActor<AActor>(SpawnItemData.ItemClass, Location, LookAtRotation, SpawnParams);
	if (!ProjectileActor) return;

	ConfirmActorSpawnDelegate.Broadcast(SpawnItemData);
	ProjectileActor->SetLifeSpan(3.f);
}

void UActorSpawnComponent::SpawnedTrapAndStructure()
{
	OnConfirmPlace.Broadcast(bCanPlaceConfirm);
	if (!PreviewActor || !bCanPlaceConfirm) return;
		
	const FVector Location = PreviewActor->GetActorLocation();
	const FRotator Rotation = PreviewActor->GetActorRotation();

	PreviewActor->Destroy();
	PreviewActor = nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ASaveMyselfActor* StructureActor =  GetWorld()->SpawnActor<ASaveMyselfActor>(SpawnItemData.ItemClass, Location, Rotation, SpawnParams);
	ConfirmActorSpawnDelegate.Broadcast(SpawnItemData);
	StructureActor->SetStructureHP(SpawnItemData.EffectValue);

	if (SpawnItemData.ItemType == EItemTypes::Structure) StructureActor->Tags.Add("Structure");
	
	SpawnItemData = FItemInformation();

	DisableEquippedItem();
}

void UActorSpawnComponent::DisableEquippedItem() const
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (ASaveMyselfPlayerController* SaveMyselfPC = Cast<ASaveMyselfPlayerController>(PC))
		{
			SaveMyselfPC->DisableKeyIndex();
		}
	}
}
