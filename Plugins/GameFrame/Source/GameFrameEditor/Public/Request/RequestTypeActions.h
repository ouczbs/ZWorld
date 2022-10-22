

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 *
 */
class FRequestTypeActions : public FAssetTypeActions_Base
{
protected:
	uint32 AssetCategory = EAssetTypeCategories::Blueprint;
public:
	FRequestTypeActions() {};
	FRequestTypeActions(uint32 InAssetCategory) : AssetCategory(InAssetCategory) {};
	//AssetName
	virtual FText GetName() const override;
	//Asset图标的颜色
	virtual FColor GetTypeColor() const override;
	//Asset的UObject是什么
	virtual UClass* GetSupportedClass() const override;
	//Asset所属的分类
	virtual uint32 GetCategories() override;

	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	bool ShouldUseDataOnlyEditor( const UBlueprint* Blueprint ) const;
};
