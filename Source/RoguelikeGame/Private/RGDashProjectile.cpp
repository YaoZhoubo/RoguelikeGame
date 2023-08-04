// RogueLike Game, All Rights Reserved.


#include "RGDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

void ARGDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DetonateDelay, this, &ARGDashProjectile::Explode, DetonateDelay);
}

void ARGDashProjectile::Explode_Implementation()
{
	//确保清除定时器，因为可能会通过其他源调用Explode（OnActorHit）
	GetWorldTimerManager().ClearTimer(TimerHandle_DetonateDelay);

	//在指定位置产生发射器
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	//禁用粒子系统
	EffectComp->DeactivateSystem();

	//立即停止运动,关闭碰撞以防触发Hit或者Overlap事件
	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	//设置第二个定时器
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ARGDashProjectile::TeleportInstigator, TeleportDelay);

}

void ARGDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		//目标位置，发起者位置，是否为一个测试，是否跳过检查侵犯其他Instigator
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}

ARGDashProjectile::ARGDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MoveComp->InitialSpeed = 6000.f;
}
