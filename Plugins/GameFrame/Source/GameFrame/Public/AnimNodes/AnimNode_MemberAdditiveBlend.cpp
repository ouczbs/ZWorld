// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimNodes/AnimNode_MemberAdditiveBlend.h"
#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimTrace.h"

#define DEFAULT_SOURCEINDEX 0xFF
/////////////////////////////////////////////////////
// FAnimNode_MemberAdditiveBlend

void FAnimNode_MemberAdditiveBlend::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
    DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Initialize_AnyThread)
	FAnimNode_Base::Initialize_AnyThread(Context);
    BasePose.Initialize(Context);
    const int NumPoses = BlendPoses.Num();
    checkSlow(BlendWeights.Num() == NumPoses);
    if (NumPoses > 0)
    {
        for (int32 ChildIndex = 0; ChildIndex < NumPoses; ++ChildIndex)
        {
            BlendPoses[ChildIndex].Initialize(Context);
        }
    }
    AlphaScaleBiasClamp.Reinitialize();
}

void FAnimNode_MemberAdditiveBlend::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
    DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(CacheBones_AnyThread)
    BasePose.CacheBones(Context);
	int32 NumPoses = BlendPoses.Num();
	for(int32 ChildIndex=0; ChildIndex<NumPoses; ChildIndex++)
	{
		BlendPoses[ChildIndex].CacheBones(Context);
	}
}

void FAnimNode_MemberAdditiveBlend::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Update_AnyThread)
	QUICK_SCOPE_CYCLE_COUNTER(STAT_FAnimationNode_TwoWayBlend_Update);
	GetEvaluateGraphExposedInputs().Execute(Context);
    BasePose.Update(Context);
    bHasRelevantPoses = false;
    int32 NumPoses = BlendPoses.Num();
    for(int32 ChildIndex=0; ChildIndex<NumPoses; ChildIndex++)
    {
        if (FAnimWeight::IsRelevant(BlendWeights[ChildIndex]))
        {
            float ActualAlpha = AlphaScaleBiasClamp.ApplyTo(BlendWeights[ChildIndex], Context.GetDeltaTime());
            BlendPoses[ChildIndex].Update(Context.FractionalWeight(ActualAlpha));
            ActualAlphas[ChildIndex] = ActualAlpha;
            bHasRelevantPoses = true;
        }
    }
}

void FAnimNode_MemberAdditiveBlend::Evaluate_AnyThread(FPoseContext& Output)
{
    DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Evaluate_AnyThread)
    BasePose.Evaluate(Output);
    if(bHasRelevantPoses){
        // evaluate children
        FAnimationPoseData OutAnimationPoseData(Output);
        const int NumPoses = BlendPoses.Num();
        for(int32 ChildIndex = 0; ChildIndex < NumPoses; ChildIndex++ )
        {
            if (FAnimWeight::IsRelevant(BlendWeights[ChildIndex]))
            {
                const bool bExpectsAdditivePose = true;
                FPoseContext AdditiveEvalContext(Output, bExpectsAdditivePose);
                BlendPoses[ChildIndex].Evaluate(AdditiveEvalContext);
                const FAnimationPoseData AdditiveAnimationPoseData(AdditiveEvalContext);
                FAnimationRuntime::AccumulateAdditivePose(OutAnimationPoseData, AdditiveAnimationPoseData, ActualAlphas[ChildIndex], AAT_LocalSpaceBase);
                Output.Pose.NormalizeRotations();
            }
        }
    } 
}

void FAnimNode_MemberAdditiveBlend::GatherDebugData(FNodeDebugData& DebugData)
{
    DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(GatherDebugData)
    BasePose.GatherDebugData(DebugData.BranchFlow(1.f));
    const int NumPoses = BlendPoses.Num();
    FString DebugLine = DebugData.GetNodeName(this);
    DebugLine += FString::Printf(TEXT("(Num Poses: %i)"), NumPoses);
    DebugData.AddDebugItem(DebugLine);
    for (int32 ChildIndex = 0; ChildIndex < NumPoses; ++ChildIndex)
    {
        BlendPoses[ChildIndex].GatherDebugData(DebugData.BranchFlow(BlendWeights[ChildIndex]));
    }
}