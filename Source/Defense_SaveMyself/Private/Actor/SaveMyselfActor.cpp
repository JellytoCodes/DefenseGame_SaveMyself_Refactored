
#include "Actor/SaveMyselfActor.h"

#include "Components/ActorEffectComponent.h"
#include "Components/BoxComponent.h"

ASaveMyselfActor::ASaveMyselfActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxCollision);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	ItemMesh->SetupAttachment(RootComponent);

	ActorEffectComponent = CreateDefaultSubobject<UActorEffectComponent>("EffectComponent");
}


