// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimTypes.h"
#include "Animation/AnimData/BoneMaskFilter.h"
#include "AnimNodes/AnimNode_LinkNodeBase.h"
#include "AnimNode_MemberBoneBlend.generated.h"

UENUM()
enum class EMemberBoneBlendMode : uint8
{
	BranchFilter,
	BlendMask,
};

// Layered blend (per bone); has dynamic number of blendposes that can blend per different bone sets
USTRUCT(BlueprintInternalUseOnly)
struct GAMEFRAME_API FAnimNode_MemberBoneBlend : public FAnimNode_LinkNodeBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Name = "AnimNode_MemberBoneBlend";
	/** Whether to use branch filters or a blend mask to specify an input pose per-bone influence */
	UPROPERTY(EditAnywhere, Category = Config)
	EMemberBoneBlendMode BlendMode;
	/** Each layer's blended pose */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, editfixedsize, Category=Links)
	TArray<FPoseLink> BlendPoses;
    /** The weights of each layer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, editfixedsize, Category=Runtime, meta=(PinShownByDefault))
	TArray<float> BlendWeights;
	/** 
	 * The blend masks to use for our layer inputs. Allows the use of per-bone alphas.
	 * Blend masks are used when BlendMode is BlendMask.
	 */
	UPROPERTY(EditAnywhere, editfixedsize, Category=Config, meta=(UseAsBlendMask=true))
	TArray<TObjectPtr<UBlendProfile>> BlendMasks;

	/** 
	 * Configuration for the parts of the skeleton to blend for each layer. Allows
	 * certain parts of the tree to be blended out or omitted from the pose.
	 * LayerSetup is used when BlendMode is BranchFilter.
	 */
	UPROPERTY(EditAnywhere, editfixedsize, Category=Config)
	TArray<FInputBlendPose> LayerSetup;

	/** Whether to blend bone rotations in mesh space or in local space */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	bool bMeshSpaceRotationBlend;

	/** Whether to blend bone scales in mesh space or in local space */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	bool bMeshSpaceScaleBlend;
	
	/** How to blend the layers together */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	TEnumAsByte<enum ECurveBlendOption::Type>	CurveBlendOption;

	/** Whether to incorporate the per-bone blend weight of the root bone when lending root motion */
	UPROPERTY(EditAnywhere, Category = Config)
	bool bBlendRootMotionBasedOnRootBone;

	bool bHasRelevantPoses;

	/*
 	 * Max LOD that this node is allowed to run
	 * For example if you have LODThreadhold to be 2, it will run until LOD 2 (based on 0 index)
	 * when the component LOD becomes 3, it will stop update/evaluate
	 * currently transition would be issue and that has to be re-visited
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold"))
	int32 LODThreshold;

protected:

	// This is buffer to serialize blend weight data for each joints
	// This has to save with the corresponding SkeletopnGuid
	// If not, it will rebuild in run-time
	UPROPERTY()
	TArray<FPerBoneBlendWeight>	PerBoneBlendWeights;

	UPROPERTY()
	FGuid						SkeletonGuid;

	UPROPERTY()
	FGuid						VirtualBoneGuid;


	// transient data to handle weight and target weight
	// this array changes based on required bones
	TArray<FPerBoneBlendWeight> DesiredBoneBlendWeights;
	TArray<FPerBoneBlendWeight> CurrentBoneBlendWeights;
	TArray<uint8> CurvePoseSourceIndices;
public:	
	FAnimNode_MemberBoneBlend()
		: BlendMode(EMemberBoneBlendMode::BranchFilter)
		, bMeshSpaceRotationBlend(false)
		, bMeshSpaceScaleBlend(false)
		, CurveBlendOption(ECurveBlendOption::Override)
		, bBlendRootMotionBasedOnRootBone(true)
		, bHasRelevantPoses(false)
		, LODThreshold(INDEX_NONE)
	{
	}

	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	virtual int32 GetLODThreshold() const override { return LODThreshold; }
	// End of FAnimNode_Base interface
	void AddPose()
	{
		BlendWeights.Add(1.f);
		new (BlendPoses) FPoseLink();
		new (LayerSetup) FInputBlendPose();
	}

	void RemovePose(int32 PoseIndex)
	{
		BlendWeights.RemoveAt(PoseIndex);
		BlendPoses.RemoveAt(PoseIndex);
		LayerSetup.RemoveAt(PoseIndex);
	}

#if WITH_EDITOR
	// ideally you don't like to get to situation where it becomes inconsistent, but this happened, 
	// and we don't know what caused this. Possibly copy/paste, but I tried copy/paste and that didn't work
	// so here we add code to fix this up manually in editor, so that they can continue working on it. 
	void ValidateData();
	// FAnimNode_Base interface
	virtual void PostCompile(const class USkeleton* InSkeleton) override;
	// end FAnimNode_Base interface
#endif

	/** Reinitialize bone weights */
	void ReinitializeBoneBlendWeights(const FBoneContainer& RequiredBones, const USkeleton* Skeleton);

	// Rebuild cache data from the skeleton
	void RebuildCacheData(const USkeleton* InSkeleton);
	bool IsCacheInvalid(const USkeleton* InSkeleton) const;
	//IAnimNodeLinkInterface
    virtual void LinkNodePose(FPoseLink& Pose)override{
		AddPose();
		BlendPoses[BlendPoses.Num() - 1].SetDynamicLinkNode(&Pose);
	};
	//End of IAnimNodeLinkInterface
};
