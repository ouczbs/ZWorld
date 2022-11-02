// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/GameLuaSubsystem.h"
#include <iostream>
#include <fstream> 
#include "HAL/FileManagerGeneric.h"
#include "Misc/FileHelper.h"
#include "UnLuaInterface.h"
#include "UI/UIStruct.h"
#include "UnLua.h"

int SetLuaData(lua_State* L) {
	if (!lua_isuserdata(L, -2)) {
		//return -1;
	}
	ULuaObject* obj = (ULuaObject*)UnLua::GetUObject(L, 1, false);
	if (obj)
		obj->SetData(L);
	return 1;
}
int GetLuaData(lua_State* L) {
	if (!lua_isuserdata(L, -1)) {
		return -1;
	}
	ULuaObject* obj = (ULuaObject*)UnLua::GetUObject(L, 1, false);
	if (obj)
		obj->GetData(L);
	return 1;
}
UGameLuaSubsystem * UGameLuaSubsystem::LuaSystem = nullptr;
void UGameLuaSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//д��
	ReloadConfig();
	LuaSystem = this;
	lua_State* L = UnLua::GetState();
	lua_getglobal(L, "UE");
	lua_pushcfunction(L , SetLuaData);
	lua_setfield(L, -2, "SetLuaData");
	lua_pushcfunction(L, GetLuaData);
	lua_setfield(L, -2, "GetLuaData");
}

void UGameLuaSubsystem::Deinitialize()
{
	LuaSystem = nullptr;
}

bool UGameLuaSubsystem::ReloadConfig()
{
	FString LoadDir = FPaths::ProjectContentDir() / TEXT("Table/BPConfig.ini");  //�ļ�·��
	if (!FFileManagerGeneric::Get().FileExists(*LoadDir)) //�ж��Ƿ�����ļ�
	{
		UE_LOG(LogTemp, Error, TEXT("Table/BPConfig.ini is not Exists!!!"));
		return false;
	}
	pb::BPConfig BPConfig;
	std::fstream in(*LoadDir, std::ios::in | std::ios::binary);
	if (!BPConfig.ParseFromIstream(&in))
	{
		UE_LOG(LogTemp, Error, TEXT("Table/BPConfig.ini ParseFromIstream error!!!"));
		return false;
	}
	auto list = BPConfig.item_list();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		LuaBPMap.Add(FName(iter->bp_name().c_str()), iter->lua_name().c_str());
	}
	//LuaBPMap;
	return true;
}
FString UGameLuaSubsystem::FindLuaModule(FString& Name)
{
	const auto module = LuaBPMap.Find(FName(Name));
	if (module)
		return *module;
	return "";
}

FString ULuaModuleLocator_ByConfig::Locate(const UObject* Object)
{
	const auto Class = Object->IsA<UClass>() ? static_cast<const UClass*>(Object) : Object->GetClass();
	FString Key = Class->GetName();
	Key.RemoveFromEnd(TEXT("_C"));
	UGameLuaSubsystem* LuaSystem = UGameLuaSubsystem::GetSystem();
	if (LuaSystem) {
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
		// CDO��û�г�ʼ�����
		return "";
	}

	if (!Class->ImplementsInterface(UUnLuaInterface::StaticClass()))
	{
		return "";
	}
	return IUnLuaInterface::Execute_GetModuleName(CDO);
}
