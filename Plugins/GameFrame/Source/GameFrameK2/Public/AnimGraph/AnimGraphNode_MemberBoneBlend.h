// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnimGraphNode_Base.h"
#include "Interface/AnimNodeBlendList.h"
#include "AnimNodes/AnimNode_MemberBoneBlend.h"
#include "AnimationNodes/SGraphNodeBlendList.h"
#include "AnimGraphNode_MemberBoneBlend.generated.h"

UCLASS(MinimalAPI)
class UAnimGraphNode_MemberBoneBlend : public UAnimGraphNode_Base , public IAnimNodeBlendList
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category=Settings)
	FAnimNode_MemberBoneBlend MemberNode;

	// UObject interface
	virtual void Serialize(FArchive& Ar) override;
	// End of UObject interface

	// Adds a new pose pin
	//@TODO: Generalize this behavior (returning a list of actions/delegates maybe?)
	virtual void AddPinToBlend() override;
	virtual void RemovePinFromBlend(UEdGraphPin* Pin) override;

	// UEdGraphNode interface
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of UEdGraphNode interface

	// UK2Node interface
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	// End of UK2Node interface

	// UAnimGraphNode_Base interface
	virtual FString GetNodeCategory() const override;
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	virtual void PreloadRequiredAssets() override;
	// End of UAnimGraphNode_Base interface


	// Gives each visual node a chance to validate that they are still valid in the context of the compiled class, giving a last shot at error or warning generation after primary compilation is finished
	virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;
	// End of UAnimGraphNode_Base interface

	// End of UAnimGraphNode_Base interface
	virtual TSharedPtr<SGraphNode> CreateVisualWidget()override{
		return SNew(SGraphNodeBlendList , this);
	};
	//~ Begin UK2Node Interface.
	virtual bool IsNodePure() const override{ return true; }
	virtual FString GetDescriptiveCompiledName() const override;
	//~ Begin UK2Node Interface.
private:
	/** Constructing FText strings can be costly, so we cache the node's title */
	FNodeTextCache CachedNodeTitle;
};
