// RogueLike Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RgAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class ROGUELIKEGAME_API ARgAIController : public AAIController
{
	GENERATED_BODY()

protected:

	//表示该属性只能通过类属性窗口（类默认值）编辑,细节窗口不能编辑。
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	virtual void BeginPlay() override;
};
