// RogueLike Game, All Rights Reserved.


#include "RGAttributeActorComponent.h"

// Sets default values for this component's properties
URGAttributeActorComponent::URGAttributeActorComponent()
{
	Health = 100;
}



bool URGAttributeActorComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}

bool URGAttributeActorComponent::IsAlive() const
{
	return Health > 0.0f;
}

