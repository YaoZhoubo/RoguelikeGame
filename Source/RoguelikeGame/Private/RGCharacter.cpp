// Fill out your copyright notice in the Description page of Project Settings.


#include "RGCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RGInteractionComponent.h"
//#include "RGAttributeActorComponent.h"

// Sets default values
ARGCharacter::ARGCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	// 在SpringArmComponent中开启“使用Pawn控制旋转”
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	// 获取“角色移动”组件，开启“将旋转朝向运动”
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	InteractionComp = CreateDefaultSubobject<URGInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<URGAttributeActorComponent>("AttributeComp");
}

// Called when the game starts or when spawned
void ARGCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ARGCharacter::MoveForWard(float Value)
{
	//获取相机的朝向
	FRotator ControlRot = GetControlRotation();
	//Roll为X轴，Pitch为Y轴，Yaw为Z轴， XYZ = 前右上
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void ARGCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ARGCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	//延时器
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ARGCharacter::PrimaryAttack_TimeElapsed, 0.18f);
	
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);

}

void ARGCharacter::BlackHoleAttack()
{
	PlayAnimMontage(AttackAnim);

	//延时器
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ARGCharacter::BlackHoleAttack_TimeElapsed, 0.18f);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);

}

void ARGCharacter::Dash()
{
	PlayAnimMontage(AttackAnim);

	//延时器
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ARGCharacter::Dash_TimeElapsed, 0.18f);

}

void ARGCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

void ARGCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}

void ARGCharacter::BlackHoleAttack_TimeElapsed()
{
	SpawnProjectile(BlackHoleProjectileClass);
}

void ARGCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashClass);
}

void ARGCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		//获取指定的位置
		FVector RightHandLoc = GetMesh()->GetSocketLocation("Muzzle_01");

		// 此处设置碰撞检测规则为：即使碰撞也总是生成，因为粒子在角色中间生成必然碰撞
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		//扫描形状
		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		//附加参数， 这里需要忽略自己
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		//扫描对象
		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		//扫描开始和结束的位置
		FVector TranceStart = CameraComponent->GetComponentLocation();
		FVector TranceEnd = CameraComponent->GetComponentLocation() + (GetActorRotation().Vector() * 5000);

		//扫描结果
		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, TranceStart, TranceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			TranceEnd = Hit.ImpactPoint;
		}
		//获取放射方向
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TranceEnd - RightHandLoc).Rotator();

		FTransform SpawnTM = FTransform(GetActorRotation(), RightHandLoc);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);

	}
}

void ARGCharacter::OnHealthChanged(AActor* InstigatorActor, URGAttributeActorComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f && Delta <= 0.0f)
	{
		APlayerController* PC =  Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

void ARGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ARGCharacter::OnHealthChanged);
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
	PlayerInputComponent->BindAxis("MoveRight", this, &ARGCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARGCharacter::Jump);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ARGCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("BlackHoleAttack", IE_Pressed, this, &ARGCharacter::BlackHoleAttack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ARGCharacter::Dash);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ARGCharacter::PrimaryInteract);
}

