// RogueLike Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RGGameplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URGGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ROGUELIKEGAME_API IRGGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//BlueprintCallable：可在蓝图中调用
	//BlueprintImplementableEvent：可在蓝图中实现
	//BlueprintNativeEvent：蓝图可调用可实现；需要被重写，但也有默认实现
	// 传入调用者。为了使不能双足行走的角色能正确调用，定义为Pawn而不是Character
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
};
