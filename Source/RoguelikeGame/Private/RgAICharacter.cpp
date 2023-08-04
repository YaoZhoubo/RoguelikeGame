// RogueLike Game, All Rights Reserved.


#include "RgAICharacter.h"

// Sets default values
ARgAICharacter::ARgAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARgAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARgAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

