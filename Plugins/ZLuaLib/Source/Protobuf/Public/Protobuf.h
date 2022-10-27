// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Features/IModularFeatures.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


class PROTOBUF_API FProtobuf : public IModuleInterface,public IModularFeature
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
