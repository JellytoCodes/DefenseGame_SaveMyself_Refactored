#include "Actor/SaveMyselfActor.h"
#include "Components/ActorEffectComponent.h"
#include "Components/BoxComponent.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Sight.h"

ASaveMyselfActor::ASaveMyselfActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxCollision);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	ItemMesh->SetupAttachment(RootComponent);

	ActorEffectComponent = CreateDefaultSubobject<UActorEffectComponent>("EffectComponent");

	StimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSourceComp"));
	StimuliSourceComp->RegisterForSense(UAISense_Sight::StaticClass());
	StimuliSourceComp->bAutoRegister = true;
}

void ASaveMyselfActor::BeginPlay()
{
	Super::BeginPlay();

	InitializeSaveMyselfActor();
}

bool ASaveMyselfActor::GetDamaged(const float InDamage)
{
	CurrentHP -= InDamage;
	const float HPPercent = FMath::Clamp(CurrentHP/StructureHP, 0.f, 1.f);

	if (DynamicMaterial)
	{
		const float Opacity = FMath::Lerp(0.3f, 1.f, HPPercent);
		DynamicMaterial->SetScalarParameterValue(FName("Opacity"), Opacity);
	}

	if (CurrentHP <= 0)
	{
		Destroy();
		return true;
	}
	return false;
}

void ASaveMyselfActor::SetStructureHP(const float InStructureHP)
{
	StructureHP = InStructureHP;
	CurrentHP = InStructureHP;
}

void ASaveMyselfActor::InitializeSaveMyselfActor()
{
	if(StimuliSourceComp)
	{
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(GetWorld(), UAISense_Sight::StaticClass(), this);
	}
	if (USaveMyselfItemSubsystem* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
	{
		ItemInfo = ItemSubsystem->GetItemInfo(ItemName);
	}

	if (ItemMesh)
	{
		if (UMaterialInterface* BaseMaterial = ItemMesh->GetMaterial(0))
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
			ItemMesh->SetMaterial(0, DynamicMaterial);
		}
	}
}
