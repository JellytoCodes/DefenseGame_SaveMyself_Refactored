// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetComponents/EffectWidgetComponent.h"

void UEffectWidgetComponent::BindingEvent(const bool State) const
{
	BindEventDelegate.Broadcast(State);
}
