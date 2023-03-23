// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FastNoise/VoxelFastNoise.h"
#include "FastNoise/VoxelFastNoise.inl"
#include "VoxelGenerators/VoxelGenerator.h"
#include "VoxelGenerators/VoxelGeneratorHelpers.h"
#include "UnLuaInterface.h"
#include "MMOVoxelGenerator.generated.h"


USTRUCT(BlueprintType)
struct FVoxelMMOGeneratorDataItemConfig
{
	GENERATED_BODY()

		// In voxels, how smooth the intersection with the existing terrain and these items should be
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		float Smoothness = 10;

	// Only items matching this mask will be added
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Bitmask, BitmaskEnum = EVoxel32BitMask))
		int32 Mask = 0;

	// If true, will subtract the items from the world and will invert their values
	// If false, will add the items to the world and will not invert their values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		bool bSubtractItems = false;
};

/**
 * 
 */
static FVoxelFastNoise FastNoise;
UCLASS()
class ZWORLD_API UMMOVoxelGenerator : public UVoxelGenerator
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Voxel")
		double IQNoise_3D(double x, double y, double z, double frequency, double octaves) const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Voxel")
		double GetValue(double X, double Y, double Z, double LOD);
	UFUNCTION(BlueprintImplementableEvent, Category = "Voxel")
	EVoxelMaterialConfig GetMaterialType(double X, double Y, double Z, double LOD);
	FVoxelMaterial GetMaterial(double X, double Y, double Z, double LOD);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
		bool bLuaObject = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
		int SingleIndex = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
		TArray<int> DesiredIndexs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
		TArray<float> DesiredAlphas;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
		FLinearColor Color = FLinearColor::Transparent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
		TArray<FVoxelMMOGeneratorDataItemConfig> DataItemConfigs =
	{
		{
			2,
			1 << 0,
			true
		},
		{
			2,
			1 << 1,
			false
		},
	};
	//~ Begin UVoxelGenerator Interface
	TVoxelSharedRef<FVoxelGeneratorInstance> GetInstance() override;
};

class FVoxelMMOGeneratorInstance : public TVoxelGeneratorInstanceHelper<FVoxelMMOGeneratorInstance, UMMOVoxelGenerator>
{
public:
	using Super = TVoxelGeneratorInstanceHelper<FVoxelMMOGeneratorInstance, UMMOVoxelGenerator>;

	const FVoxelMaterial Material;
	const TArray<FVoxelMMOGeneratorDataItemConfig> DataItemConfigs;
	UMMOVoxelGenerator* LuaObject;
	explicit FVoxelMMOGeneratorInstance(UMMOVoxelGenerator& Object)
		: Super(&Object)
		, LuaObject(&Object)
		, Material(FVoxelMaterial::CreateFromColor(Object.Color))
		, DataItemConfigs(Object.DataItemConfigs)
	{
	}

	//~ Begin FVoxelGeneratorInstance Interface
	v_flt GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;
	TVoxelRange<v_flt> GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const;
	FVoxelMaterial GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;
	FVector GetUpVector(v_flt X, v_flt Y, v_flt Z) const override final;
	//~ End FVoxelGeneratorInstance Interface
};