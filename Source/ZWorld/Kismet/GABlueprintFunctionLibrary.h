

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GABlueprintFunctionLibrary.generated.h"

/**
 * class ATELIER_API UGABlueprintFunctionLibrary : public UBlueprintFunctionLibrary
 */

 // 用于加载完成的回调
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAsyncLoadFinished , bool , IsSuccess);
UCLASS()
class ZWORLD_API UGABlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "C++ Library")
	static void SwitchMaterialWithParams(class UMaterialInterface* OriginMat, class UMaterialInstanceDynamic* NewMat);

	UFUNCTION(BlueprintCallable)
	static void AsyncLoadPackage(FName& PackageName,const FOnAsyncLoadFinished& OnAsyncLoadFinished);

	UFUNCTION(BlueprintCallable)
		static float GetLoadProgress(FName& PackageName);
};
