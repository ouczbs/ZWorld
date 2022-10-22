// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimGraphNode_MemberBoneBlend.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ToolMenu.h"
#include "AnimGraphCommands.h"
#include "ScopedTransaction.h"
#include "DetailLayoutBuilder.h"
#include "Kismet2/CompilerResultsLog.h"
/////////////////////////////////////////////////////
// UAnimGraphNode_MemberBoneBlend

#define LOCTEXT_NAMESPACE "A3Nodes"

UAnimGraphNode_MemberBoneBlend::UAnimGraphNode_MemberBoneBlend(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MemberNode.AddPose();
}

FLinearColor UAnimGraphNode_MemberBoneBlend::GetNodeTitleColor() const
{
	return FLinearColor(0.2f, 0.8f, 0.2f);
}

FText UAnimGraphNode_MemberBoneBlend::GetTooltipText() const
{
	return LOCTEXT("AnimGraphNode_MemberBoneBlend_Tooltip", "Layered blend per bone");
}

void UAnimGraphNode_MemberBoneBlend::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName PropertyName = (PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None);

	// Reconstruct node to show updates to PinFriendlyNames.
	if (PropertyName == GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_MemberBoneBlend, BlendMode))
	{
		// If we  change blend modes, we need to resize our containers
		MemberNode.ValidateData();
		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

FString UAnimGraphNode_MemberBoneBlend::GetNodeCategory() const
{
	return TEXT("Blend Member Nodes");
}

void UAnimGraphNode_MemberBoneBlend::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TSharedRef<IPropertyHandle> NodeHandle = DetailBuilder.GetProperty(FName(TEXT("Node")), GetClass());

	if (MemberNode.BlendMode != EMemberBoneBlendMode::BranchFilter)
	{
		DetailBuilder.HideProperty(NodeHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAnimNode_MemberBoneBlend, LayerSetup)));
	}

	if (MemberNode.BlendMode != EMemberBoneBlendMode::BlendMask)
	{
		DetailBuilder.HideProperty(NodeHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAnimNode_MemberBoneBlend, BlendMasks)));
	}

	Super::CustomizeDetails(DetailBuilder);
}

void UAnimGraphNode_MemberBoneBlend::PreloadRequiredAssets()
{
	// Preload our blend profiles in case they haven't been loaded by the skeleton yet.
	if (MemberNode.BlendMode == EMemberBoneBlendMode::BlendMask)
	{
		int32 NumBlendMasks = MemberNode.BlendMasks.Num();
		for (int32 MaskIndex = 0; MaskIndex < NumBlendMasks; ++MaskIndex)
		{
			UBlendProfile* BlendMask = MemberNode.BlendMasks[MaskIndex];
			PreloadObject(BlendMask);
		}
	}

	Super::PreloadRequiredAssets();
}

void UAnimGraphNode_MemberBoneBlend::AddPinToBlend()
{
	FScopedTransaction Transaction( LOCTEXT("AddPinToBlend", "AddPinToBlendByFilter") );
	Modify();

	MemberNode.AddPose();
	ReconstructNode();
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
}

void UAnimGraphNode_MemberBoneBlend::RemovePinFromBlend(UEdGraphPin* Pin)
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

void UAnimGraphNode_MemberBoneBlend::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if (!Context->bIsDebugging)
	{
		{
			FToolMenuSection& Section = Menu->AddSection("AnimGraphNodeLayeredBoneblend", LOCTEXT("LayeredBoneBlend", "Layered Bone Blend"));
			if (Context->Pin != NULL)
			{
				// we only do this for normal BlendList/BlendList by enum, BlendList by Bool doesn't support add/remove pins
				if (Context->Pin->Direction == EGPD_Input)
				{
					//@TODO: Only offer this option on arrayed pins
					Section.AddMenuEntry(FAnimGraphCommands::Get().RemoveBlendListPin);
				}
			}
			else
			{
				Section.AddMenuEntry(FAnimGraphCommands::Get().AddBlendListPin);
			}
		}
	}
}

void UAnimGraphNode_MemberBoneBlend::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	MemberNode.ValidateData();
}

void UAnimGraphNode_MemberBoneBlend::ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog)
{
	UAnimGraphNode_Base::ValidateAnimNodeDuringCompilation(ForSkeleton, MessageLog);

	bool bCompilationError = false;
	// Validate blend masks
	if (MemberNode.BlendMode == EMemberBoneBlendMode::BlendMask)
	{
		int32 NumBlendMasks = MemberNode.BlendMasks.Num();
		for (int32 MaskIndex = 0; MaskIndex < NumBlendMasks; ++MaskIndex)
		{
			const UBlendProfile* BlendMask = MemberNode.BlendMasks[MaskIndex];
			if (BlendMask == nullptr)
			{
				MessageLog.Error(*FText::Format(LOCTEXT("LayeredBlendNullMask", "@@ has null BlendMask for Blend Pose {0}. "), FText::AsNumber(MaskIndex)).ToString(), this, BlendMask);
				bCompilationError = true;
				continue;
			}
			else if (BlendMask->Mode != EBlendProfileMode::BlendMask)
			{
				MessageLog.Error(*FText::Format(LOCTEXT("LayeredBlendProfileModeError", "@@ is using a BlendProfile(@@) without a BlendMask mode for Blend Pose {0}. "), FText::AsNumber(MaskIndex)).ToString(), this, BlendMask);
				bCompilationError = true;
			}
		}
	}

	// Don't rebuild the node's data if compilation failed. We may be attempting to do so with invalid data.
	if (bCompilationError)
	{
		return;
	}

	// ensure to cache the data
 	if (MemberNode.IsCacheInvalid(ForSkeleton))
 	{
 		MemberNode.RebuildCacheData(ForSkeleton);
 	}
}
FText UAnimGraphNode_MemberBoneBlend::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("EnumName"), FText::FromString(MemberNode.Name));
	// FText::Format() is slow, so we cache this to save on performance
	CachedNodeTitle.SetCachedText(FText::Format(LOCTEXT("BlendBoneByChannel", "MemberBoneBlend({EnumName})"), Args), this);
	return CachedNodeTitle;
}
FString UAnimGraphNode_MemberBoneBlend::GetDescriptiveCompiledName() const
{
	return MemberNode.Name;
}
#undef LOCTEXT_NAMESPACE
