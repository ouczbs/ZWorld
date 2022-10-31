// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameFrame.h"
#include "UnLuaSettings.h"
#include "Config/BPSubSystemSetting.h"
#include "Subsystem/GameLuaSubsystem.h"

#define LOCTEXT_NAMESPACE "FGameFrameModule"

void FGameFrameModule::StartupModule()
{
	auto Settings = GetMutableDefault<UUnLuaSettings>();
	Settings->ModuleLocatorClass = ULuaModuleLocator_ByConfig::StaticClass();
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FGameFrameModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameFrameModule, GameFrame)