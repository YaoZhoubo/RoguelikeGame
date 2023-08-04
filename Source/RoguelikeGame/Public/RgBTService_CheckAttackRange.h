// RogueLike Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RgBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKEGAME_API URgBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
	

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	//该类在行为树中被引用时，在细节面板中暴露关键帧选择
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

};
