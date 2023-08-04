// RogueLike Game, All Rights Reserved.


#include "RGItemChest.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARGItemChest::ARGItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;
}

void ARGItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	// 相对base进行旋转，参数(pitch, yaw, roll)
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

// Called when the game starts or when spawned
void ARGItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARGItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

