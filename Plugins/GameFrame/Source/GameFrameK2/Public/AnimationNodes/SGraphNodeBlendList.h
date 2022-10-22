// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "AnimationNodes/SAnimationGraphNode.h"

class SVerticalBox;
class FBaseNodeBlendList;

class SGraphNodeBlendList : public SAnimationGraphNode
{
public:
	SLATE_BEGIN_ARGS(SGraphNodeBlendList){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode);

protected:
	// SGraphNode interface
	virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox) override;
	virtual FReply OnAddPin() override;
	// End of SGraphNode interface
};
