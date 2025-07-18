
#include "Components/StageManagerComponent.h"
#include "Game/Subsystem/SaveMyselfStageSubsystem.h"

UStageManagerComponent::UStageManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UStageManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
