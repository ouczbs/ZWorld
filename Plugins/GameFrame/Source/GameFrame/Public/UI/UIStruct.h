// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIStruct.generated.h"

USTRUCT(BlueprintType)
struct GAMEFRAME_API FUIItemData
{
	GENERATED_USTRUCT_BODY()

	FUIItemData()
	{
		IsSelected = false;
	}

public:
	UPROPERTY(EditAnyWhere)
	bool IsSelected;
};