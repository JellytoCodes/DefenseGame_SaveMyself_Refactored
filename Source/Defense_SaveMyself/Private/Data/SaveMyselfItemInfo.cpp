
#include "Data/SaveMyselfItemInfo.h"

FItemInformation::FItemInformation() :
ItemName(NAME_None), ItemType(EItemTypes::None), ItemIcon(nullptr), EffectValue(0.f), EffectRadius(0.f), EffectType(EEffectTypes::None), ItemClass(nullptr),
ItemWeight(0.f), NameDisplay(FText()), Description(FText()), TypeDisplay(FText())
{
}
