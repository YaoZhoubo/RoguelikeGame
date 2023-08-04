// RogueLike Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RGMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ROGUELIKEGAME_API ARGMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARGMagicProjectile();

	UPROPERTY(EditAnywhere, Category = "Damage")
	float damage = 20.0f;

protected:

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 球体,用于计算碰撞
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	// 投射体，控制球体的运动
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	// 粒子系统，控制特效
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
