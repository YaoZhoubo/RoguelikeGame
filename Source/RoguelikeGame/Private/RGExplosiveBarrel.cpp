// RogueLike Game, All Rights Reserved.


#include "RGExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ARGExplosiveBarrel::ARGExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// UE中的“模拟物理”选项
	MeshComp->SetSimulatePhysics(true);
	// 等同于在UE中将“碰撞预设”设置为“PhysicsActor”
	MeshComp->SetCollisionProfileName("PhysicsActor");
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	ForceComp->Radius = 750.0f;			 // 爆炸范围
	ForceComp->ImpulseStrength = 700.0f; // 冲击力
	ForceComp->bImpulseVelChange = true; // 忽略质量大小；见UE中ForceComp的“冲量速度变更”

}

void ARGExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	// log信息的category，log/warning/error等表示日志的详细程度，打印的文字内容
	UE_LOG(LogTemp, Log, TEXT("OtherActor is %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	UE_LOG(LogTemp, Warning, TEXT("HHHHHHHHHHHHH"));

	FString CombStr = FString::Printf(TEXT("Hit at %s"), *Hit.ImpactPoint.ToString());
	// 获取世界，位置，打印的内容，需要attach的actor，颜色，持续时间，是否有影子
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombStr, nullptr, FColor::Green, 2.0f, true);
}

// Called when the game starts or when spawned
void ARGExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	MeshComp->OnComponentHit.AddDynamic(this, &ARGExplosiveBarrel::OnActorHit);
	
}

// Called every frame
void ARGExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

