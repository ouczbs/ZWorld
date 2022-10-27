// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/GameLuaSubsystem.h"
#include <iostream>
#include <fstream> 
#include "HAL/FileManagerGeneric.h"

void UGameLuaSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	FString LoadDir = FPaths::ProjectContentDir() / TEXT("Table/BPConfig.ini");  //文件路径
	if (!FFileManagerGeneric::Get().FileExists(*LoadDir)) //判断是否存在文件
	{
		UE_LOG(LogTemp, Error, TEXT("Table/BPConfig.ini is not Exists!!!"));
		return;
	}
	std::fstream in(*LoadDir, std::ios::in | std::ios::binary);
	if (!mConfig.ParseFromIstream(&in))
	{
		UE_LOG(LogTemp, Error, TEXT("Parse error!!!"));
	}
	LuaSystem = this;
}

void UGameLuaSubsystem::Deinitialize()
{
	LuaSystem = nullptr;
}

FString UGameLuaSubsystem::FindLuaModule(FString& Name)
{
	auto& map = mConfig.item_map();
	auto iterator = map.find(Name);
	if (iterator != map.end()) {
		return (*iterator).second.c_str();
	}
	return Name;
}

FString ULuaModuleLocator_ByConfig::Locate(const UObject* Object)
{
	UGameLuaSubsystem* LuaSystem = UGameLuaSubsystem::GetSystem();
	const auto Class = Object->IsA<UClass>() ? static_cast<const UClass*>(Object) : Object->GetClass();
	FString Key = Class->GetFName().ToString();
	if (LuaSystem) {
		return LuaSystem->FindLuaModule(Key);
	}
	return Key;
}
