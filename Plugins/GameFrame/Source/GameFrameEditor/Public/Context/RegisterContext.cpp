#include "RegisterContext.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
void FRegisterContext::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}
void FRegisterContext::UnregisterAssetTypeActions(IAssetTools& AssetTools)
{
	for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
	{
		AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
	}
}
void FRegisterContext::RegisterCustomClassLayout(FPropertyEditorModule& PropertyEditor, FName ClassName, FOnGetDetailCustomizationInstance DetailLayoutDelegate) {
	PropertyEditor.RegisterCustomClassLayout(ClassName, DetailLayoutDelegate);
	CreatedAssetDetailName.Add(ClassName);
}

void FRegisterContext::UnregisterCustomClassLayouts(FPropertyEditorModule& PropertyEditor) {
	for (int32 Index = 0; Index < CreatedAssetDetailName.Num(); ++Index)
	{
		PropertyEditor.UnregisterCustomClassLayout(CreatedAssetDetailName[Index]);
	}
}
void FRegisterContext::RegisterCustomPropertyTypeLayout(FPropertyEditorModule& PropertyEditor, FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate) {
	PropertyEditor.RegisterCustomPropertyTypeLayout(PropertyTypeName, PropertyTypeLayoutDelegate);
	CreatedPropertyName.Add(PropertyTypeName);
}

void FRegisterContext::UnregisterCustomPropertyTypeLayout(FPropertyEditorModule& PropertyEditor) {
	for (int32 Index = 0; Index < CreatedPropertyName.Num(); ++Index)
	{
		PropertyEditor.UnregisterCustomPropertyTypeLayout(CreatedPropertyName[Index]);
	}
}
void FRegisterContext::UnregisterAllAction() {
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) {
		return;
	}
	IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	UnregisterAssetTypeActions(AssetTools);
	UnregisterCustomClassLayouts(PropertyModule);
	UnregisterCustomPropertyTypeLayout(PropertyModule);
}

