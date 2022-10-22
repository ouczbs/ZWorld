#pragma once

#include "CoreMinimal.h"
#include "Interface/PoolObjectInterface.h"
#include "AnimNodes/AnimNode_LinkNodeBase.h"
#include "AnimOwner.generated.h"
/**
 * 基于UE4引擎的游戏寻路功能设计与优化
 */
class URequest;
USTRUCT()
struct FAnimLinkPropertyResult {
    GENERATED_USTRUCT_BODY()
    FAnimLinkPropertyResult(int32 InIndex, FStructProperty* InProperty) {
        Index = InIndex;
        Property = InProperty;
    };
    FAnimLinkPropertyResult(){};
    int32 Index;
    FStructProperty* Property;
};
UCLASS(Blueprintable)
class GAMEFRAME_API UAnimOwner : public UObject ,  public IPoolObjectInterface
{
	GENERATED_BODY()
public:
    void Initialize(UAnimInstance* InAnimInstance);
    FAnimNode_LinkNodeBase* FindAnimNodeByName(FName Name , int32& OutIndex);
    void LinkAnimNode(FAnimNode_LinkNodeBase * SourceNode, int32 index , FName Name );
private:
    UAnimInstance* AnimInstance;
    IAnimClassInterface* AnimClassInterface;
    TMap<FName , FAnimLinkPropertyResult> AnimLinkPropertyResultMap;
	FAnimNode_LinkNodeBase* MainNode;
    int32 MainIndex;
    FAnimNode_LinkNodeBase* OverLayNode;
    int32 OverLayIndex;
    FAnimNode_LinkNodeBase* AdditiveNode;
    int32 AdditiveIndex;
};
