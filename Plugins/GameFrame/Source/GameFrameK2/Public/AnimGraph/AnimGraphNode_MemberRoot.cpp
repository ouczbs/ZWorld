// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimGraphNode_MemberRoot.h"

/////////////////////////////////////////////////////
// UAnimGraphNode_MemberRoot

#define LOCTEXT_NAMESPACE "AnimGraphNode_MemberRoot"

UAnimGraphNode_MemberRoot::UAnimGraphNode_MemberRoot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
FString UAnimGraphNode_MemberRoot::GetDescriptiveCompiledName() const
{
	return MemberNode.Name;
}
FString UAnimGraphNode_MemberRoot::GetNodeCategory() const
{
	return TEXT("Blend Member Nodes");
}

FLinearColor UAnimGraphNode_MemberRoot::GetNodeTitleColor() const
{
	return FLinearColor(0.75f, 0.75f, 0.75f);
}

FText UAnimGraphNode_MemberRoot::GetTooltipText() const
{
	return LOCTEXT("BlendBoneByChannelTooltip", "Member Node as Anim Instance.");
}

FText UAnimGraphNode_MemberRoot::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("EnumName"), FText::FromString(MemberNode.Name));
	// FText::Format() is slow, so we cache this to save on performance
	CachedNodeTitle.SetCachedText(FText::Format(LOCTEXT("BlendBoneByChannel", "MemberRoot({EnumName})"), Args), this);
	return CachedNodeTitle;
}

#undef LOCTEXT_NAMESPACE

