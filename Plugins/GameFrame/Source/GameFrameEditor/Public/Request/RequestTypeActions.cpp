#include "RequestTypeActions.h"

#include "BlueprintEditorModule.h"
#include "BlueprintEditor.h"
#include "Logging/MessageLog.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Requests/Request.h"
#define LOCTEXT_NAMESPACE "FRequestTypeActions"
//资源名
FText FRequestTypeActions::GetName() const
{
	return LOCTEXT("FRequestTypeActions", "Request");
}
//资源目录
uint32 FRequestTypeActions::GetCategories()
{
	return AssetCategory;
}
//图标颜色
FColor FRequestTypeActions::GetTypeColor() const
{
	return FColor(100, 175, 241);
}
//资源对应的 UClass
UClass* FRequestTypeActions::GetSupportedClass() const
{
	return URequestBlueprint::StaticClass();
}
bool FRequestTypeActions::ShouldUseDataOnlyEditor( const UBlueprint* Blueprint ) const
{
	return FBlueprintEditorUtils::IsDataOnlyBlueprint(Blueprint) 
		&& !FBlueprintEditorUtils::IsLevelScriptBlueprint(Blueprint) 
		&& !FBlueprintEditorUtils::IsInterfaceBlueprint(Blueprint)
		&& !Blueprint->bForceFullEditor
		&& !Blueprint->bIsNewlyCreated;
}
void FRequestTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* Object : InObjects)
	{
		if (UBlueprint* Blueprint = Cast<UBlueprint>(Object))
		{
			bool bLetOpen = true;
			if (!Blueprint->SkeletonGeneratedClass || !Blueprint->GeneratedClass)
			{
				bLetOpen = EAppReturnType::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("FailedToLoadBlueprintWithContinue", "Blueprint could not be loaded because it derives from an invalid class.  Check to make sure the parent class for this blueprint hasn't been removed! Do you want to continue (it can crash the editor)?"));
			}
			if (bLetOpen)
			{
				FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
				TSharedRef< IBlueprintEditor > NewKismetEditor = BlueprintEditorModule.CreateBlueprintEditor(Mode, EditWithinLevelEditor, Blueprint, ShouldUseDataOnlyEditor(Blueprint));
			}
		}
		else
		{
			FMessageDialog::Open( EAppMsgType::Ok, LOCTEXT("FailedToLoadBlueprint", "Blueprint could not be loaded because it derives from an invalid class.  Check to make sure the parent class for this blueprint hasn't been removed!"));
		}
	}
}

#undef LOCTEXT_NAMESPACE