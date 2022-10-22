#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_LinkNodeBase.generated.h"
USTRUCT(BlueprintInternalUseOnly)
struct GAMEFRAME_API FAnimNode_LinkNodeBase : public FAnimNode_Base
{
	GENERATED_BODY()

public:
	//IAnimNodeLinkInterface
    virtual void LinkNodePose(FPoseLink& Pose){};
	//End of IAnimNodeLinkInterface
};