

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimNodes/AnimNode_LinkNodeBase.h"
#include "NodeAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFRAME_API UNodeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MemberNode")
	void LinkNodePose(FAnimNode_LinkNodeBase& SourceNode, FAnimNode_LinkNodeBase& TargetNode);
};
