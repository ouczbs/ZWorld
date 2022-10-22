// Copyright Epic Games, Inc. All Rights Reserved.


#include "AnimationNodes/SGraphNodeBlendList.h"
#include "Interface/AnimNodeBlendList.h"
#include "GraphEditorSettings.h"

/////////////////////////////////////////////////////
// SGraphNodeBlendList

void SGraphNodeBlendList::Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode)
{
	this->GraphNode = (UEdGraphNode*) InNode;

	this->SetCursor(EMouseCursor::CardinalCross);

	this->UpdateGraphNode();

	SAnimationGraphNode::Construct(SAnimationGraphNode::FArguments(), InNode);
}

void SGraphNodeBlendList::CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox)
{
	TSharedRef<SWidget> AddPinButton = AddPinButtonContent(
		NSLOCTEXT("LayeredBoneBlendNode", "LayeredBoneBlendNodeAddPinButton", "Add pin"),
		NSLOCTEXT("LayeredBoneBlendNode", "LayeredBoneBlendNodeAddPinButton_Tooltip", "Adds a input pose to the node"),
		false);

	FMargin AddPinPadding = Settings->GetInputPinPadding();
	AddPinPadding.Top += 6.0f;

	InputBox->AddSlot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.Padding(AddPinPadding)
		[
			AddPinButton
		];
}

FReply SGraphNodeBlendList::OnAddPin()
{
	if(IAnimNodeBlendList* BlendList = Cast<IAnimNodeBlendList>(GraphNode)){
		BlendList->AddPinToBlend();
	}
	return FReply::Handled();
}
