// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RGAttributeActorComponent.h"
#include "RGCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class URGInteractionComponent;
class UAnimMontage;

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

	// 投射体子类
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(VisibleAnywhere)
	URGInteractionComponent* InteractionComp;

	FTimerHandle TimerHandle_PrimaryAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URGAttributeActorComponent* AttributeComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForWard(float Value);
	void MoveRight(float Value);

	void PrimaryAttack();
	void BlackHoleAttack();
	void Dash();
	void PrimaryInteract();

	void PrimaryAttack_TimeElapsed();
	void BlackHoleAttack_TimeElapsed();
	void Dash_TimeElapsed();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, URGAttributeActorComponent* OwningComp, float NewHealth, float Delta);

	void  virtual PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
