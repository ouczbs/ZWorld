


#include "Animation/NodeAnimInstance.h"

void UNodeAnimInstance::LinkNodePose(FAnimNode_LinkNodeBase& SourceNode , FAnimNode_LinkNodeBase& TargetNode)
{
    //FPoseLink Pose = TargetNode.GetNodePose();
    //SourceNode.LinkNodePose(Pose);
    /*
    if (!TargetNode.HasCacheBones()){
        FAnimInstanceProxy* Proxy = &GetProxyOnAnyThread<FAnimInstanceProxy>();
        FAnimationUpdateSharedContext SharedContext;
        FAnimationInitializeContext InitContext(Proxy, &SharedContext);
        TargetNode.Initialize_AnyThread(InitContext);
    }
    if (!TargetNode.HasCacheBones()) {
        InitializeAnimation(false);
    }
    */
}