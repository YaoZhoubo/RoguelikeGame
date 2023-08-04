// RogueLike Game, All Rights Reserved.


#include "RGMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "RGAttributeActorComponent.h"

// Sets default values
ARGMagicProjectile::ARGMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("RGProjectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARGMagicProjectile::OnActorOverlap);
	RootComponent = SphereComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp); 

}

void ARGMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		//获得AttributeComp
		URGAttributeActorComponent* AttributeComp = Cast<URGAttributeActorComponent>(OtherActor->GetComponentByClass(URGAttributeActorComponent::StaticClass()));
		// 再次判空，可能碰到的是墙壁、箱子等没有血量的物体
		if (AttributeComp)
		{
			// 魔法粒子造成20血量伤害
			AttributeComp->ApplyHealthChange(damage);
			// 一旦造成伤害就销毁，避免穿过角色继续计算
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ARGMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARGMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

