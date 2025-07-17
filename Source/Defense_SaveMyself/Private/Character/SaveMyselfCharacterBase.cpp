#include "Character/SaveMyselfCharacterBase.h"

ASaveMyselfCharacterBase::ASaveMyselfCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ASaveMyselfCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASaveMyselfCharacterBase::InitializeCharacterInfo()
{

}

void ASaveMyselfCharacterBase::Die()
{
	Destroy();
}