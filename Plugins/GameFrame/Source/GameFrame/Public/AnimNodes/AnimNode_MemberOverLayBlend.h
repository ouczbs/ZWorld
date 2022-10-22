// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimTypes.h"
#include "Animation/AnimData/BoneMaskFilter.h"
#include "AnimNodes/AnimNode_LinkNodeBase.h"
#include "AnimNode_MemberOverLayBlend.generated.h"


// Layered blend (per bone); has dynamic number of blendposes that can blend per different bone sets
USTRUCT(BlueprintInternalUseOnly)
struct GAMEFRAME_API FAnimNode_MemberOverLayBlend : public FAnimNode_LinkNodeBase
{
	GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere)
	FString Name = "AnimNode_MemberOverLayBlend";
	/** The source pose */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FPoseLink BasePose;
	/** Each layer's blended pose */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, editfixedsize, Category=Links)
	TArray<FPoseLink> BlendPoses;
    /** The weights of each layer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, editfixedsize, Category=Runtime, meta=(PinShownByDefault))
	TArray<float> BlendWeights;
public:	
	FAnimNode_MemberOverLayBlend()
	{
	}
	void AddPose()
	{
		BlendWeights.Add(1.f);
		new (BlendPoses) FPoseLink();
	}

	void RemovePose(int32 PoseIndex)
	{
		BlendWeights.RemoveAt(PoseIndex);
		BlendPoses.RemoveAt(PoseIndex);
	}
	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	// End of FAnimNode_Base interface

	//IAnimNodeLinkInterface
    virtual void LinkNodePose(FPoseLink& Pose)override{
		AddPose();
		BlendPoses[BlendPoses.Num() - 1].SetDynamicLinkNode(&Pose);
	};
	//End of IAnimNodeLinkInterface
private:
	bool bHasRelevantPoses;
};
