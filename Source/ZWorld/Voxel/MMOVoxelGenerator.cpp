// Fill out your copyright notice in the Description page of Project Settings.


#include "Voxel/MMOVoxelGenerator.h"
#include "VoxelUtilities/VoxelDataItemUtilities.h"
#include "MMOVoxelGenerator.h"
#include <VoxelMaterialBuilder.h>


FVoxelMaterial UMMOVoxelGenerator::GetMaterial(float X, float Y, float Z, float LOD)
{
	FVoxelMaterialBuilder Builder;
	auto type = GetMaterialType(X ,Y ,Z ,LOD);
	Builder.SetMaterialConfig(type);
	switch (type)
	{
	case EVoxelMaterialConfig::RGB:
		Builder.SetColor(FColor::Red);
		break;
	case EVoxelMaterialConfig::SingleIndex:
		Builder.SetSingleIndex(SingleIndex); 
		break;
	case EVoxelMaterialConfig::DoubleIndex_DEPRECATED:
		break;
	case EVoxelMaterialConfig::MultiIndex:
		for (int i = 0; i < DesiredIndexs.Num(); i++)
		{
			Builder.AddMultiIndex(DesiredIndexs[i], DesiredAlphas[i]);
		}
		break;
	default:
		break;
	}
	return Builder.Build();
}

//
TVoxelSharedRef<FVoxelGeneratorInstance> UMMOVoxelGenerator::GetInstance()
{
	return MakeVoxelShared<FVoxelMMOGeneratorInstance>(*this);
}

v_flt FVoxelMMOGeneratorInstance::GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
	if (LuaObject && LuaObject->bLuaObject) {
		return LuaObject->GetValue(X ,Y ,Z ,LOD );
	}
	v_flt Density = Z + 0.001f; // Try to avoid having 0 as density, as it behaves weirdly

	if (Items.ItemHolder.GetDataItems().Num() > 0)
	{
		for (auto& DataItemConfig : DataItemConfigs)
		{
			if (DataItemConfig.bSubtractItems)
			{
				Density = FVoxelUtilities::CombineDataItemDistance<true>(Density, Items.ItemHolder, X, Y, Z, DataItemConfig.Smoothness, DataItemConfig.Mask, EVoxelDataItemCombineMode::Max);
			}
			else
			{
				Density = FVoxelUtilities::CombineDataItemDistance<false>(Density, Items.ItemHolder, X, Y, Z, DataItemConfig.Smoothness, DataItemConfig.Mask, EVoxelDataItemCombineMode::Min);
			}
		}
	}

	return Density;
}

TVoxelRange<v_flt> FVoxelMMOGeneratorInstance::GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const
{
	const auto X = TVoxelRange<v_flt>(Bounds.Min.X, Bounds.Max.X);
	const auto Y = TVoxelRange<v_flt>(Bounds.Min.Y, Bounds.Max.Y);
	const auto Z = TVoxelRange<v_flt>(Bounds.Min.Z, Bounds.Max.Z);

	auto Density = Z + 0.001f;

	if (Items.ItemHolder.GetDataItems().Num() > 0)
	{
		for (auto& DataItemConfig : DataItemConfigs)
		{
			if (DataItemConfig.bSubtractItems)
			{
				Density = FVoxelUtilities::CombineDataItemDistanceRange<true>(Density, Items.ItemHolder, X, Y, Z, DataItemConfig.Smoothness, DataItemConfig.Mask, EVoxelDataItemCombineMode::Max);
			}
			else
			{
				Density = FVoxelUtilities::CombineDataItemDistanceRange<false>(Density, Items.ItemHolder, X, Y, Z, DataItemConfig.Smoothness, DataItemConfig.Mask, EVoxelDataItemCombineMode::Min);
			}
		}
	}

	return Density;
}

FVoxelMaterial FVoxelMMOGeneratorInstance::GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
	if (LuaObject && LuaObject->bLuaObject) {
		return LuaObject->GetMaterial(X, Y, Z, LOD);
	}
	return Material;
}

FVector FVoxelMMOGeneratorInstance::GetUpVector(v_flt X, v_flt Y, v_flt Z) const
{
	return FVector::UpVector;
}
