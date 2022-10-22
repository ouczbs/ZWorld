// Coypright

#include "GameFrameEditor.h"
#include "GameTag/GameTagCustomization.h"
#include "ToolMenu/EditorMenuExtensions.h"
#include "Request/RequestTypeActions.h"
#include "Tag/GameTag.h"
#include "IAssetTools.h"
void FGameFrameEditorModule::StartupModule()
{
	if (!GIsEditor)
		return;
	FEditorMenuExtensions::ExtendMenus();
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	RegisterContext.RegisterCustomPropertyTypeLayout(PropertyModule, FGameTag::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FPropertyGameTagCustomization::MakeInstance));
	// Register asset categories.
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	RegisterContext.RegisterAssetTypeAction(AssetTools, MakeShareable(new FRequestTypeActions(EAssetTypeCategories::Blueprint)));
}
void FGameFrameEditorModule::ShutdownModule()
{
	RegisterContext.UnregisterAllAction();
}

IMPLEMENT_GAME_MODULE(FGameFrameEditorModule, GameFrameEditor);