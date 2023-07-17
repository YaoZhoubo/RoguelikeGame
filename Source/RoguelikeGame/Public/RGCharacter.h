// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RGCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;


UCLASS()
class ROGUELIKEGAME_API ARGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARGCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForWard(float Value);
	void MoveRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
