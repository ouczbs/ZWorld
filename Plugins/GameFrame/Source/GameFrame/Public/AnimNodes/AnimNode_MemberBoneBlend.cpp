// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimNodes/AnimNode_MemberBoneBlend.h"
#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimTrace.h"

#define DEFAULT_SOURCEINDEX 0xFF
/////////////////////////////////////////////////////
// FAnimNode_MemberBoneBlend

void FAnimNode_MemberBoneBlend::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Initialize_AnyThread)
	FAnimNode_Base::Initialize_AnyThread(Context);
	const int NumPoses = BlendPoses.Num();
	checkSlow(BlendWeights.Num() == NumPoses);
	if (NumPoses > 0)
	{
		for (int32 ChildIndex = 0; ChildIndex < NumPoses; ++ChildIndex)
		{
			BlendPoses[ChildIndex].Initialize(Context);
		}
	}
}

#if WITH_EDITOR
void FAnimNode_MemberBoneBlend::PostCompile(const class USkeleton* InSkeleton)
{
	FAnimNode_Base::PostCompile(InSkeleton);
	RebuildCacheData(InSkeleton);
}
#endif // WITH_EDITOR

void FAnimNode_MemberBoneBlend::RebuildCacheData(const USkeleton* InSkeleton)
{
	if (InSkeleton)
	{
		if (BlendMode == EMemberBoneBlendMode::BranchFilter)
		{
			FAnimationRuntime::CreateMaskWeights(PerBoneBlendWeights, LayerSetup, InSkeleton);
		}
		else
		{
			FAnimationRuntime::CreateMaskWeights(PerBoneBlendWeights, BlendMasks, InSkeleton);
		}

		SkeletonGuid = InSkeleton->GetGuid();
		VirtualBoneGuid = InSkeleton->GetVirtualBoneGuid();
	}
}

bool FAnimNode_MemberBoneBlend::IsCacheInvalid(const USkeleton* InSkeleton) const
{
	return (InSkeleton->GetGuid() != SkeletonGuid || InSkeleton->GetVirtualBoneGuid() != VirtualBoneGuid);
}

void FAnimNode_MemberBoneBlend::ReinitializeBoneBlendWeights(const FBoneContainer& RequiredBones, const USkeleton* Skeleton)
{
	if (IsCacheInvalid(Skeleton))
	{
		RebuildCacheData(Skeleton);
	}
	
	// build desired bone weights
	const TArray<FBoneIndexType>& RequiredBoneIndices = RequiredBones.GetBoneIndicesArray();
	const int32 NumRequiredBones = RequiredBoneIndices.Num();
	DesiredBoneBlendWeights.SetNumZeroed(NumRequiredBones);
	for (int32 RequiredBoneIndex=0; RequiredBoneIndex<NumRequiredBones; RequiredBoneIndex++)
	{
		const int32 SkeletonBoneIndex = RequiredBones.GetSkeletonIndex(FCompactPoseBoneIndex(RequiredBoneIndex));
		if (ensure(SkeletonBoneIndex != INDEX_NONE))
		{
			DesiredBoneBlendWeights[RequiredBoneIndex] = PerBoneBlendWeights[SkeletonBoneIndex];
		}
	}
	
	CurrentBoneBlendWeights.Reset(DesiredBoneBlendWeights.Num());
	CurrentBoneBlendWeights.AddZeroed(DesiredBoneBlendWeights.Num());

	//Reinitialize bone blend weights now that we have cleared them
	FAnimationRuntime::UpdateDesiredBoneWeight(DesiredBoneBlendWeights, CurrentBoneBlendWeights, BlendWeights);

	TArray<uint16> const& CurveUIDFinder = RequiredBones.GetUIDToArrayLookupTable();
	const int32 CurveUIDCount = CurveUIDFinder.Num();
	const int32 TotalCount = FBlendedCurve::GetValidElementCount(&CurveUIDFinder);
	if (TotalCount > 0)
	{
		CurvePoseSourceIndices.Reset(TotalCount);
		// initialize with FF - which is default
		CurvePoseSourceIndices.Init(DEFAULT_SOURCEINDEX, TotalCount);

		// now go through point to correct source indices. Curve only picks one source index
		for (int32 UIDIndex = 0; UIDIndex < CurveUIDCount; ++UIDIndex)
		{
			int32 CurrentPoseIndex = CurveUIDFinder[UIDIndex];
			if (CurrentPoseIndex != MAX_uint16)
			{
				SmartName::UID_Type CurveUID = (SmartName::UID_Type)UIDIndex;

				const FCurveMetaData* CurveMetaData = Skeleton->GetCurveMetaData(CurveUID);
				if (CurveMetaData)
				{
					const TArray<FBoneReference>& LinkedBones = CurveMetaData->LinkedBones;
					for (int32 LinkedBoneIndex = 0; LinkedBoneIndex < LinkedBones.Num(); ++LinkedBoneIndex)
					{
						FCompactPoseBoneIndex CompactPoseIndex = LinkedBones[LinkedBoneIndex].GetCompactPoseIndex(RequiredBones);
						if (CompactPoseIndex != INDEX_NONE)
						{
							if (DesiredBoneBlendWeights[CompactPoseIndex.GetInt()].BlendWeight > 0.f)
							{
								CurvePoseSourceIndices[CurrentPoseIndex] = DesiredBoneBlendWeights[CompactPoseIndex.GetInt()].SourceIndex;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		CurvePoseSourceIndices.Reset();
	}
}

void FAnimNode_MemberBoneBlend::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(CacheBones_AnyThread)
	int32 NumPoses = BlendPoses.Num();
	for(int32 ChildIndex=0; ChildIndex<NumPoses; ChildIndex++)
	{
		BlendPoses[ChildIndex].CacheBones(Context);
	}
	if (BlendPoses.Num() > 0)
	{
		ReinitializeBoneBlendWeights(Context.AnimInstanceProxy->GetRequiredBones(), Context.AnimInstanceProxy->GetSkeleton());
	}
}

void FAnimNode_MemberBoneBlend::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Update_AnyThread)
	bHasRelevantPoses = false;
	int32 RootMotionBlendPose = -1;
	float RootMotionWeight = 0.f;
	const float RootMotionClearWeight = bBlendRootMotionBasedOnRootBone ? 0.f : 1.f;

	if (IsLODEnabled(Context.AnimInstanceProxy))
	{
		GetEvaluateGraphExposedInputs().Execute(Context);

		for (int32 ChildIndex = 0; ChildIndex < BlendPoses.Num(); ++ChildIndex)
		{
			const float ChildWeight = BlendWeights[ChildIndex];
			if (FAnimWeight::IsRelevant(ChildWeight))
			{
				if (bHasRelevantPoses == false)
				{
					// If our cache is invalid, attempt to update it.
					if (IsCacheInvalid(Context.AnimInstanceProxy->GetSkeleton()))
					{
						ReinitializeBoneBlendWeights(Context.AnimInstanceProxy->GetRequiredBones(), Context.AnimInstanceProxy->GetSkeleton());

						// If Cache is still invalid, we don't have correct DesiredBoneBlendWeights, so abort.
						// bHasRelevantPoses == false, will passthrough in evaluate.
						if (!ensure(IsCacheInvalid(Context.AnimInstanceProxy->GetSkeleton())))
						{
							break;
						}
					}
					else
					{
						FAnimationRuntime::UpdateDesiredBoneWeight(DesiredBoneBlendWeights, CurrentBoneBlendWeights, BlendWeights);
					}

					bHasRelevantPoses = true;

					if(bBlendRootMotionBasedOnRootBone)
					{
						const float NewRootMotionWeight = CurrentBoneBlendWeights[0].BlendWeight;
						if(NewRootMotionWeight > ZERO_ANIMWEIGHT_THRESH)
						{
							RootMotionWeight = NewRootMotionWeight;
							RootMotionBlendPose = CurrentBoneBlendWeights[0].SourceIndex;
						}
					}
				}

				const float ThisPoseRootMotionWeight = (ChildIndex == RootMotionBlendPose) ? RootMotionWeight : RootMotionClearWeight;
				BlendPoses[ChildIndex].Update(Context.FractionalWeightAndRootMotion(ChildWeight, ThisPoseRootMotionWeight));
			}
		}
	}
	else
	{
		// Clear BlendWeights if disabled by LODThreshold.
		BlendWeights.Init(0.f, BlendWeights.Num());
	}

	TRACE_ANIM_NODE_VALUE(Context, TEXT("Num Poses"), BlendPoses.Num());
}

void FAnimNode_MemberBoneBlend::Evaluate_AnyThread(FPoseContext& Output)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Evaluate_AnyThread)
	ANIM_MT_SCOPE_CYCLE_COUNTER(BlendPosesInGraph, !IsInGameThread());
	const int NumPoses = BlendPoses.Num();
	if ((NumPoses != 0) && bHasRelevantPoses)
	{
		FPoseContext BasePoseContext(Output);
		BasePoseContext.Pose.CopyBonesFrom(Output.Pose);
		BasePoseContext.Curve.CopyFrom(Output.Curve);
		BasePoseContext.CustomAttributes.CopyFrom(Output.CustomAttributes);

		TArray<FCompactPose> TargetBlendPoses;
		TargetBlendPoses.SetNum(NumPoses);

		TArray<FBlendedCurve> TargetBlendCurves;
		TargetBlendCurves.SetNum(NumPoses);

		TArray<UE::Anim::FStackAttributeContainer> TargetBlendAttributes;
		TargetBlendAttributes.SetNum(NumPoses);

		for (int32 ChildIndex = 0; ChildIndex < NumPoses; ++ChildIndex)
		{
			if (FAnimWeight::IsRelevant(BlendWeights[ChildIndex]))
			{
				FPoseContext CurrentPoseContext(Output);
				BlendPoses[ChildIndex].Evaluate(CurrentPoseContext);

				TargetBlendPoses[ChildIndex].MoveBonesFrom(CurrentPoseContext.Pose);
				TargetBlendCurves[ChildIndex].MoveFrom(CurrentPoseContext.Curve);
				TargetBlendAttributes[ChildIndex].MoveFrom(CurrentPoseContext.CustomAttributes);
			}
			else
			{
				TargetBlendPoses[ChildIndex].ResetToRefPose(BasePoseContext.Pose.GetBoneContainer());
				TargetBlendCurves[ChildIndex].InitFrom(Output.Curve);
			}
		}

		// filter to make sure it only includes curves that is linked to the correct bone filter
		TArray<uint16> const* CurveUIDFinder = Output.Curve.UIDToArrayIndexLUT;
		const int32 TotalCount = Output.Curve.NumValidCurveCount;
		// now go through point to correct source indices. Curve only picks one source index
		for (int32 UIDIndex = 0; UIDIndex < CurveUIDFinder->Num(); ++UIDIndex)
		{
			int32 CurvePoseIndex = Output.Curve.GetArrayIndexByUID(UIDIndex);
			if (CurvePoseSourceIndices.IsValidIndex(CurvePoseIndex))
			{
				int32 SourceIndex = CurvePoseSourceIndices[CurvePoseIndex];
				if (SourceIndex != DEFAULT_SOURCEINDEX)
				{
					// if source index is set, clear base pose curve value
					BasePoseContext.Curve.Set(UIDIndex, 0.f);
					for (int32 ChildIndex = 0; ChildIndex < NumPoses; ++ChildIndex)
					{
						if (SourceIndex != ChildIndex)
						{
							// if not source, clear it
							TargetBlendCurves[ChildIndex].Set(UIDIndex, 0.f);
						}
					}
				}
			}
		}

		FAnimationRuntime::EBlendPosesPerBoneFilterFlags BlendFlags = FAnimationRuntime::EBlendPosesPerBoneFilterFlags::None;
		if (bMeshSpaceRotationBlend)
		{
			BlendFlags |= FAnimationRuntime::EBlendPosesPerBoneFilterFlags::MeshSpaceRotation;
		}
		if (bMeshSpaceScaleBlend)
		{
			BlendFlags |= FAnimationRuntime::EBlendPosesPerBoneFilterFlags::MeshSpaceScale;
		}

		FAnimationPoseData AnimationPoseData(Output);
		//FAnimationRuntime::BlendPosesPerBoneFilter(BasePoseContext.Pose, TargetBlendPoses, BasePoseContext.Curve, TargetBlendCurves, BasePoseContext.CustomAttributes, TargetBlendAttributes, AnimationPoseData, CurrentBoneBlendWeights, BlendFlags, CurveBlendOption);
	}
}


void FAnimNode_MemberBoneBlend::GatherDebugData(FNodeDebugData& DebugData)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(GatherDebugData)
    const int NumPoses = BlendPoses.Num();
	FString DebugLine = DebugData.GetNodeName(this);
	DebugLine += FString::Printf(TEXT("(Num Poses: %i)"), NumPoses);
	DebugData.AddDebugItem(DebugLine);
	for (int32 ChildIndex = 0; ChildIndex < NumPoses; ++ChildIndex)
	{
		BlendPoses[ChildIndex].GatherDebugData(DebugData.BranchFlow(BlendWeights[ChildIndex]));
	}
}

#if WITH_EDITOR
void FAnimNode_MemberBoneBlend::ValidateData()
{
	// ideally you don't like to get to situation where it becomes inconsistent, but this happened, 
	// and we don't know what caused this. Possibly copy/paste, but I tried copy/paste and that didn't work
	// so here we add code to fix this up manually in editor, so that they can continue working on it. 
	int32 PoseNum = BlendPoses.Num();
	int32 WeightNum = BlendWeights.Num();
	int32 LayerNum = (BlendMode == EMemberBoneBlendMode::BranchFilter) ? LayerSetup.Num() : BlendMasks.Num();

	int32 Max = FMath::Max3(PoseNum, WeightNum, LayerNum);
	int32 Min = FMath::Min3(PoseNum, WeightNum, LayerNum);
	// if they are not all same
	if (Min != Max)
	{
		// we'd like to increase to all Max
		// sadly we don't have add X for how many
		for (int32 Index=PoseNum; Index<Max; ++Index)
		{
			BlendPoses.Add(FPoseLink());
		}

		for(int32 Index=WeightNum; Index<Max; ++Index)
		{
			BlendWeights.Add(1.f);
		}

		if (BlendMode == EMemberBoneBlendMode::BranchFilter)
		{
			for (int32 Index = LayerNum; Index < Max; ++Index)
			{
				LayerSetup.Add(FInputBlendPose());
			}
		}
		else
		{
			// Get rid of our branch filters if we are not using them to avoid saving into the asset
			LayerSetup.Reset();
		}

		if (BlendMode == EMemberBoneBlendMode::BlendMask)
		{
			for (int32 Index = LayerNum; Index < Max; ++Index)
			{
				BlendMasks.Add(nullptr);
			}
		}
		else
		{
			// Get rid of blend masks array if we are not using them to avoid saving into the asset
			BlendMasks.Reset();
		}
	}
}
#endif
