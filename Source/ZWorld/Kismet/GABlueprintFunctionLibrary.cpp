// Fill out your copyright notice in the Description page of Project Settings.


#include "GABlueprintFunctionLibrary.h"


void UGABlueprintFunctionLibrary::SwitchMaterialWithParams(UMaterialInterface* OriginMaterial, UMaterialInstanceDynamic* NewMaterial)
{
	TArray<FMaterialParameterInfo> OutParameterInfo;
	TArray<FGuid> OutParameterIds;
	UMaterialInterface* originMaterial = OriginMaterial;
	UMaterialInstanceDynamic* newMaterial = NewMaterial;

	originMaterial->GetAllScalarParameterInfo(OutParameterInfo, OutParameterIds);
	for (FMaterialParameterInfo SPInfo : OutParameterInfo)
	{
		float Value;
		bool ret = originMaterial->GetScalarParameterValue(SPInfo, Value);
		if (ret)
			newMaterial->SetScalarParameterValue(SPInfo.Name, Value);
	}

	OutParameterInfo.Reset();
	OutParameterIds.Reset();

	originMaterial->GetAllVectorParameterInfo(OutParameterInfo, OutParameterIds);
	for (FMaterialParameterInfo SPInfo : OutParameterInfo)
	{
		FLinearColor Value;
		bool ret = originMaterial->GetVectorParameterValue(SPInfo, Value);
		if (ret)
			newMaterial->SetVectorParameterValue(SPInfo.Name, Value);
	}

	OutParameterInfo.Reset();
	OutParameterIds.Reset();

	originMaterial->GetAllTextureParameterInfo(OutParameterInfo, OutParameterIds);
	for (FMaterialParameterInfo SPInfo : OutParameterInfo)
	{
		UTexture *Value;
		bool ret = originMaterial->GetTextureParameterValue(SPInfo, Value);
		if (ret)
			newMaterial->SetTextureParameterValue(SPInfo.Name, Value);
	}

	OutParameterInfo.Reset();
	OutParameterIds.Reset();

	originMaterial->GetAllFontParameterInfo(OutParameterInfo, OutParameterIds);
	for (FMaterialParameterInfo SPInfo : OutParameterInfo)
	{
		UFont *Value;
		int32 FontPage;
		bool ret = originMaterial->GetFontParameterValue(SPInfo, Value, FontPage);
		if (ret)
			newMaterial->SetFontParameterValue(SPInfo.Name, Value, FontPage);
	}
}

void UGABlueprintFunctionLibrary::AsyncLoadPackage(FName& PackageName, const FOnAsyncLoadFinished& OnAsyncLoadFinished)
{
	auto LoadPackagePath = FPaths::GetBaseFilename(PackageName.ToString(), false);
	LoadPackageAsync(
		LoadPackagePath,
		FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
			{
				bool IsSuccess = Result == EAsyncLoadingResult::Succeeded;
				OnAsyncLoadFinished.ExecuteIfBound(IsSuccess);
			}), 0, PKG_ContainsMap);
}

float UGABlueprintFunctionLibrary::GetLoadProgress(FName& PackageName)
{
	float FloatPercentage = GetAsyncLoadPercentage(PackageName);
	FloatPercentage = FMath::Clamp(FloatPercentage / 100, 0.f, 1.f);
	return FloatPercentage;
}
