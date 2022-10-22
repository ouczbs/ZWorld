


#include "AnimOwner.h"
void UAnimOwner::Initialize(UAnimInstance* InAnimInstance){
    AnimInstance = InAnimInstance;
    AnimClassInterface =  Cast<IAnimClassInterface>(InAnimInstance);
}
FAnimNode_LinkNodeBase* UAnimOwner::FindAnimNodeByName(FName Name , int32& OutIndex ){
/*
    if(!AnimInstance || !AnimClassInterface){
        return nullptr;
    }
    if(AnimLinkPropertyResultMap.Contains(Name)){
        FAnimLinkPropertyResult* Result = AnimLinkPropertyResultMap.FindRef(Name);
        OutIndex = Result->Index;
        return Result->Node->ContainerPtrToValuePtr<FAnimNode_LinkNodeBase>(AnimInstance);
    }
    static UScriptStruct* LinkNodeStruct = FAnimNode_LinkNodeBase::StaticStruct();
    const TArray<FStructProperty*>& AnimNodeProperties = AnimClassInterface->GetAnimNodeProperties();
    int32 Num = AnimNodeProperties.Num();
    FStructProperty * NodeProperty;
    OutIndex = INDEX_NONE;
    for (int32 Index = 0; Index < Num; ++Index)
    {
        NodeProperty = AnimNodeProperties[Index];
        if (NodeProperty->GetFName() == Name && NodeProperty->IsChildOf(LinkNodeStruct))
		{
            OutIndex = Index;
            AnimNodePropertyMap.Add(Name , FAnimLinkPropertyResult(Index , NodeProperty));
			return NodeProperty->ContainerPtrToValuePtr<FAnimNode_LinkNodeBase>(AnimInstance);
		}
    }

*/
    return nullptr;
}
void UAnimOwner::LinkAnimNode(FAnimNode_LinkNodeBase * SourceNode, int32 index , FName Name ){
    /*
    if(!SourceNode){
        return ;
    }
    int32 OutIndex;
    if( FAnimNode_LinkNodeBase * AnimNode = FindAnimNodeByName(Name , OutIndex) ){
        FPoseLink Pose();
        Pose.LinkID = OutIndex;
        Pose.SourceLinkID = index;
        SourceNode->LinkNodePose(Pose);
    }
    */
}
