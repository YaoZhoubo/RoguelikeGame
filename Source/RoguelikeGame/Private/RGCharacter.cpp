// Fill out your copyright notice in the Description page of Project Settings.


#include "RGCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARGCharacter::ARGCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void ARGCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ARGCharacter::MoveForWard(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

// Called every frame
void ARGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARGCharacter::MoveForWard);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
}

