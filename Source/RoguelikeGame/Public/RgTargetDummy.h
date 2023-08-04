// RogueLike Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RgTargetDummy.generated.h"

class URGAttributeComponent;

UCLASS()
class ROGUELIKEGAME_API ARgTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARgTargetDummy();

protected:

	UPROPERTY(VisibleAnywhere)
	URGAttributeActorComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, URGAttributeActorComponent* OwningComp, float NewHealth, float Delta);

};
