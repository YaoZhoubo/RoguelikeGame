// RogueLike Game, All Rights Reserved.


#include "RgTargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "RGAttributeActorComponent.h"

// Sets default values
ARgTargetDummy::ARgTargetDummy()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<URGAttributeActorComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &ARgTargetDummy::OnHealthChanged);

}

void ARgTargetDummy::OnHealthChanged(AActor* InstigatorActor, URGAttributeActorComponent* OwningComp, float NewHealth, float Delta)
{
	// 治愈(>0)或免疫(=0)时不触发受击特效
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

