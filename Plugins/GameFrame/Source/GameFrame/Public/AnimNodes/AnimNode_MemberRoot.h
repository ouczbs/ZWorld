#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnimNodes/AnimNode_LinkNodeBase.h"
#include "AnimNode_MemberRoot.generated.h"
USTRUCT(BlueprintInternalUseOnly)
struct GAMEFRAME_API FAnimNode_MemberRoot : public FAnimNode_LinkNodeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FString Name = "AnimNode_MemberRoot";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
		FPoseLink Result;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Asset, meta = (PinShownByDefault, AllowPrivateAccess))
    // FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	// End of FAnimNode_Base interface
	bool HasInitialize(){
		return bInitialize;
	};
	bool HasCacheBones(){
		return bCacheBones;
	};
	//IAnimNodeLinkInterface
    virtual void LinkNodePose(FPoseLink& Pose)override{
		Result.SetDynamicLinkNode(&Pose);
	};
	//End of IAnimNodeLinkInterface
private:

	bool bInitialize = false;
	bool bCacheBones = false;
};