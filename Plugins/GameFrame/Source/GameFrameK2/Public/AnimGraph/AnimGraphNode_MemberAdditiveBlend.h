// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnimGraphNode_Base.h"
#include "Interface/AnimNodeBlendList.h"
#include "AnimNodes/AnimNode_MemberAdditiveBlend.h"
#include "AnimationNodes/SGraphNodeBlendList.h"
#include "AnimGraphNode_MemberAdditiveBlend.generated.h"

UCLASS(MinimalAPI)
class UAnimGraphNode_MemberAdditiveBlend : public UAnimGraphNode_Base , public IAnimNodeBlendList
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_MemberAdditiveBlend MemberNode;

	virtual void AddPinToBlend() override;
	virtual void RemovePinFromBlend(UEdGraphPin* Pin) override;
	
	//~ Begin UK2Node Interface.
	virtual bool IsNodePure() const override{ return true; }
	virtual FString GetDescriptiveCompiledName() const override;
	//~ Begin UK2Node Interface.

	//~ Begin UEdGraphNode Interface.
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	//~ End UEdGraphNode Interface.

	//~ Begin UAnimGraphNode_Base Interface
	virtual FString GetNodeCategory() const override;
		// End of UAnimGraphNode_Base interface
	virtual TSharedPtr<SGraphNode> CreateVisualWidget()override{
		return SNew(SGraphNodeBlendList , this);
	};
	//~ End UAnimGraphNode_Base Interface
private:
	/** Constructing FText strings can be costly, so we cache the node's title */
	FNodeTextCache CachedNodeTitle;
};
