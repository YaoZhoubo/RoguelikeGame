// RogueLike Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RGProjectileBase.h"
#include "RGDashProjectile.generated.h"

UCLASS()
class ROGUELIKEGAME_API ARGDashProjectile : public ARGProjectileBase
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay;

	FTimerHandle TimerHandle_DetonateDelay;

	virtual void BeginPlay() override;

	virtual void Explode_Implementation() override;

	void TeleportInstigator();

public:

	ARGDashProjectile();

};
