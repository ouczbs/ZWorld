// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZLuaLib.h"
#include "LuaProtobuf.h"
//#include "LibLuasocket.h"
#include "UnLuaDelegates.h"
#include "UnLua.h"
#define LOCTEXT_NAMESPACE "FZLuaLib"

void FZLuaLib::StartupModule()
{
	FUnLuaDelegates::OnLuaContextInitialized.AddRaw(this , &FZLuaLib::OnRegisterLuaLib);
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FZLuaLib::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}
void FZLuaLib::OnRegisterLuaLib(){
	lua_State* L = UnLua::GetState();
	FLuaProtobuf& LuaProtobuf = FModuleManager::LoadModuleChecked<FLuaProtobuf>(TEXT("LuaProtobuf"));
    LuaProtobuf.RegisterLuaLib(L);
	//FLibLuasocket& Luasocket = FModuleManager::LoadModuleChecked<FLibLuasocket>(TEXT("LibLuasocket"));
    //Luasocket.SetupLuasocket(L);
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FZLuaLib, ZLuaLib)