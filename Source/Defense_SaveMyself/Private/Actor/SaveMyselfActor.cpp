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

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	SetRootComponent(ItemMesh);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetupAttachment(RootComponent);

	ActorEffectComponent = CreateDefaultSubobject<UActorEffectComponent>("EffectComponent");

	StimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSourceComp"));
	StimuliSourceComp->RegisterForSense(UAISense_Sight::StaticClass());
	StimuliSourceComp->bAutoRegister = true;
}

void ASaveMyselfActor::BeginPlay()
{
	Super::BeginPlay();

	if(StimuliSourceComp)
	{
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(GetWorld(), UAISense_Sight::StaticClass(), this);
	}
	if (USaveMyselfItemSubsystem* ItemSubsystem = USaveMyselfItemSubsystem::GetItemSubSystem(this))
	{
		ItemInfo = ItemSubsystem->GetItemInfo(ItemName);
	}
}

bool ASaveMyselfActor::GetDamaged(const float InDamage)
{
	if ((StructureHP -= InDamage) <= 0)
	{
		Destroy();
		return true;
	}
	return false;
}

void ASaveMyselfActor::SetStructureHP(const float InStructureHP)
{
	StructureHP = InStructureHP;
}
