// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimGraphNode_MemberOverLayBlend.h"

/////////////////////////////////////////////////////
// UAnimGraphNode_MemberOverLayBlend

#define LOCTEXT_NAMESPACE "AnimGraphNode_MemberOverLayBlend"

UAnimGraphNode_MemberOverLayBlend::UAnimGraphNode_MemberOverLayBlend(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
FString UAnimGraphNode_MemberOverLayBlend::GetDescriptiveCompiledName() const
{
	return MemberNode.Name;
}
FString UAnimGraphNode_MemberOverLayBlend::GetNodeCategory() const
{
	return TEXT("Blend Member Nodes");
}

FLinearColor UAnimGraphNode_MemberOverLayBlend::GetNodeTitleColor() const
{
	return FLinearColor(0.75f, 0.75f, 0.75f);
}

FText UAnimGraphNode_MemberOverLayBlend::GetTooltipText() const
{
	return LOCTEXT("BlendBoneByChannelTooltip", "Member Node OverLay Blend List.");
}

FText UAnimGraphNode_MemberOverLayBlend::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("EnumName"), FText::FromString(MemberNode.Name));
	// FText::Format() is slow, so we cache this to save on performance
	CachedNodeTitle.SetCachedText(FText::Format(LOCTEXT("BlendBoneByChannel", "MemberOverLay({EnumName})"), Args), this);
	return CachedNodeTitle;
}
void UAnimGraphNode_MemberOverLayBlend::AddPinToBlend()
{
	FScopedTransaction Transaction( LOCTEXT("AddPinToBlend", "AddPinToBlendByFilter") );
	Modify();

	MemberNode.AddPose();
	ReconstructNode();
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
}

void UAnimGraphNode_MemberOverLayBlend::RemovePinFromBlend(UEdGraphPin* Pin)
{
	FScopedTransaction Transaction( LOCTEXT("RemovePinFromBlend", "RemovePinFromBlendByFilter") );
	Modify();

	FProperty* AssociatedProperty;
	int32 ArrayIndex;
	GetPinAssociatedProperty(GetFNodeType(), Pin, /*out*/ AssociatedProperty, /*out*/ ArrayIndex);

	if (ArrayIndex != INDEX_NONE)
	{
		//@TODO: ANIMREFACTOR: Need to handle moving pins below up correctly
		// setting up removed pins info 
		MemberNode.RemovePose(ArrayIndex);
		ReconstructNode();
		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
	}
}
#undef LOCTEXT_NAMESPACE

