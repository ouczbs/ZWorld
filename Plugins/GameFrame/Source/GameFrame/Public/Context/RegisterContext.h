#pragma once

#include "CoreMinimal.h"
#include "PropertyEditorModule.h"
class IAssetTools;
class IAssetTypeActions;


class GAMEFRAME_API FRegisterContext
{
public:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
	void UnregisterAssetTypeActions(IAssetTools& AssetTools);

	void RegisterCustomClassLayout(FPropertyEditorModule& PropertyEditor , FName ClassName , FOnGetDetailCustomizationInstance DetailLayoutDelegate);
	void UnregisterCustomClassLayouts(FPropertyEditorModule& PropertyEditor);

	void RegisterCustomPropertyTypeLayout(FPropertyEditorModule& PropertyEditor, FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate);
	void UnregisterCustomPropertyTypeLayout(FPropertyEditorModule& PropertyEditorModule);
	void UnregisterAllAction();
private:
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
	TArray<FName> CreatedAssetDetailName;
	TArray<FName> CreatedPropertyName;
};