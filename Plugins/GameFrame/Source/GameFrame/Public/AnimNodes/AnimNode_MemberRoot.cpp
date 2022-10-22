
#include "AnimNode_MemberRoot.h"
#include "Animation/BlendSpace.h"
/////////////////////////////////////////////////////
// FAnimNode_MemberRoot
void FAnimNode_MemberRoot::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_Base::Initialize_AnyThread(Context);
	Result.Initialize(Context);
	bInitialize = true;
}

void FAnimNode_MemberRoot::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	Result.CacheBones(Context);
	bCacheBones = true;
}

void FAnimNode_MemberRoot::Update_AnyThread(const FAnimationUpdateContext& Context)
{
    Result.Update(Context);
}

void FAnimNode_MemberRoot::Evaluate_AnyThread(FPoseContext& Output)
{
	Result.Evaluate(Output);
}
