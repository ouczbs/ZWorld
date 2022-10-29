// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/GameLuaSubsystem.h"
#include <iostream>
#include <fstream> 
#include "HAL/FileManagerGeneric.h"
#include "Misc/FileHelper.h"
#include "UnLuaInterface.h"

UGameLuaSubsystem * UGameLuaSubsystem::LuaSystem = nullptr;
void UGameLuaSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//写入
	ReloadConfig();
	ReloadTestConfig();
	LuaSystem = this;
}

void UGameLuaSubsystem::Deinitialize()
{
	LuaSystem = nullptr;
}

bool UGameLuaSubsystem::ReloadConfig()
{
	FString LoadDir = FPaths::ProjectContentDir() / TEXT("Table/BPConfig.ini");  //文件路径
	if (!FFileManagerGeneric::Get().FileExists(*LoadDir)) //判断是否存在文件
	{
		UE_LOG(LogTemp, Error, TEXT("Table/BPConfig.ini is not Exists!!!"));
		return false;
	}
	pb::BPConfig config2;
	FString resultString;
	FFileHelper::LoadFileToString(resultString, *LoadDir);

	std::fstream in(*LoadDir, std::ios::in | std::ios::binary);
	if (!config2.ParseFromIstream(&in))
	{
		mConfig.ParseFromString(TCHAR_TO_UTF8(*resultString));
		UE_LOG(LogTemp, Error, TEXT("Parse error!!!"));
		return false;
	}
	return true;
}
bool UGameLuaSubsystem::ReloadTestConfig()
{
	FString LoadDir = FPaths::ProjectContentDir() / TEXT("Table/TestConfig.ini");  //文件路径
	if (!FFileManagerGeneric::Get().FileExists(*LoadDir)) //判断是否存在文件
	{
		UE_LOG(LogTemp, Error, TEXT("Table/BPConfig.ini is not Exists!!!"));
		return false;
	}
	pb::TestConfig test;
	FString resultString;
	FFileHelper::LoadFileToString(resultString, *LoadDir);

	std::fstream in(*LoadDir, std::ios::in | std::ios::binary);
	if (!test.ParseFromIstream(&in))
	{
		UE_LOG(LogTemp, Error, TEXT("Parse error!!!"));
	}
	auto b = test.b();
	auto c = test.c();
	auto d = test.d();
	int size = d.size();
	if (size > 0) {
		auto e = d.Get(0);
	}
	
	auto a = test.a();
	if (!test.ParseFromString(TCHAR_TO_UTF8(*resultString))) {
		UE_LOG(LogTemp, Error, TEXT("Parse error!!! ParseFromString"));
	}
	//UE_LOG(LogTemp, Error, c);
	// Write the new address book back to disk.
	std::fstream output(*LoadDir, std::ios::out | std::ios::trunc | std::ios::binary);
	test.SerializeToOstream(&output);
	UE_LOG(LogTemp, Error, TEXT("Parse success!!!"));
	return true;
}
FString UGameLuaSubsystem::FindLuaModule(FString& Name)
{
	auto& map = mConfig.item_list();
	/*
	auto iterator = map.find(TCHAR_TO_UTF8(*Name));
	if (iterator != map.end()) {
		return (*iterator).second.c_str();
	}
	*/
	return "";
}

FString ULuaModuleLocator_ByConfig::Locate(const UObject* Object)
{
	const auto Class = Object->IsA<UClass>() ? static_cast<const UClass*>(Object) : Object->GetClass();
	FString Key = Class->GetName();
	Key.RemoveFromEnd(TEXT("_C"));
	UGameLuaSubsystem* LuaSystem = UGameLuaSubsystem::GetSystem();
	if (LuaSystem ) {
		FString Result = LuaSystem->FindLuaModule(Key);
		if (!Result.IsEmpty()) {
			return Result;
		}
	}
	const UObject* CDO;
	if (Object->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		CDO = Object;
	}
	else
	{
		CDO = Class->GetDefaultObject();
	}
	if (CDO->HasAnyFlags(RF_NeedInitialization))
	{
		// CDO还没有初始化完成
		return "";
	}

	if (!Class->ImplementsInterface(UUnLuaInterface::StaticClass()))
	{
		return "";
	}
	return IUnLuaInterface::Execute_GetModuleName(CDO);
}
