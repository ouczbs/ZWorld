// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/GameLuaSubsystem.h"
#include <iostream>
#include <fstream> 
#include "HAL/FileManagerGeneric.h"
#include "Misc/FileHelper.h"
#include "UnLuaInterface.h"
#include "UI/UIStruct.h"
#include "UnLua.h"
#define LOCTEXT_NAMESPACE "UGameLuaSubsystem"

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
	//写入
	ReloadConfig();
	LuaSystem = this;
	lua_State* L = UnLua::GetState();
	lua_getglobal(L, "UE");
	lua_pushcfunction(L , SetLuaData);
	lua_setfield(L, -2, "SetLuaData");
	lua_pushcfunction(L, GetLuaData);
	lua_setfield(L, -2, "GetLuaData");

#ifdef ENABLE_HOT_RELOAD_LUA_SCRIPTS
	uint32 mMaxChange = 16384;
	mBufferLength = sizeof(FILE_NOTIFY_INFORMATION) * mMaxChange;
	mBuffer = new uint8[mBufferLength];
	mBackBuffer = new uint8[mBufferLength];
	memset(mBuffer, 0, mBufferLength);
	FString RootPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + "\\Script");
	mDirectoryHandle = ::CreateFileW(
		*RootPath,
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		NULL
	);
	WatchScriptDirectorChange();
#endif // ENABLE_HOT_RELOAD_LUA_SCRIPTS
}

void UGameLuaSubsystem::Deinitialize()
{
	LuaSystem = nullptr;
#ifdef ENABLE_HOT_RELOAD_LUA_SCRIPTS
	delete mBuffer;
	delete mBackBuffer;
#endif // ENABLE_HOT_RELOAD_LUA_SCRIPTS
}

void UGameLuaSubsystem::Tick(float DeltaTime)
{
	if (LuaScriptMap.IsEmpty())
		return;
	for (auto iter = LuaScriptMap.CreateIterator();iter;++iter)
	{
		FName& script = *iter;
		//消息框显示的消息内容
		FText DialogText = FText::Format(
			LOCTEXT("UGameLuaSubsystem", "{0} is modified need to reload"),
			FText::FromName(script),
			FText::FromString(TEXT("SimpleEditors.cpp"))
		);
		EAppReturnType::Type ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText);
		if (ReturnType == EAppReturnType::Type::Ok)
		{
			lua_State* L = UnLua::GetState();
			lua_getglobal(L, "UnLua");
			lua_getfield(L, -1, "HotReload");
			lua_pushstring(L, TCHAR_TO_UTF8(*script.ToString()));
			lua_pcall(L, 1, 0, NULL);
			UE_LOG(LogTemp, Log, TEXT("HotReload filename is %s"), *script.ToString());
		}
		iter.RemoveCurrent();
	}
	//MsgWaitForMultipleObjectsEx(1, &mDirectoryHandle, 0, QS_ALLEVENTS, MWMO_ALERTABLE);
}
void ChangeNotification(::DWORD Error, ::DWORD NumBytes, LPOVERLAPPED InOverlapped) {
	UGameLuaSubsystem* LuaSystem = UGameLuaSubsystem::GetSystem();
	if (!LuaSystem)
		return;
	LuaSystem->ProcessChange(Error, NumBytes);
}
void UGameLuaSubsystem::WatchScriptDirectorChange() {
	uint32 mNotifyFilter = FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME
		| FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION;
	OVERLAPPED Overlapped;
	memset(&Overlapped, 0, sizeof(OVERLAPPED));
	const bool bSuccess = !!::ReadDirectoryChangesW(
		mDirectoryHandle,
		mBuffer,
		mBufferLength,
		true,
		mNotifyFilter,
		NULL,
		&Overlapped,
		&ChangeNotification
	);
	if (!bSuccess) {
		::CloseHandle(mDirectoryHandle);
		mDirectoryHandle = INVALID_HANDLE_VALUE;
		return;
	}
}
void UGameLuaSubsystem::ProcessChange(uint32 Error, uint32 NumBytes)
{
	if (Error == ERROR_OPERATION_ABORTED)
		return;
	const bool bValidNotification = (Error != ERROR_IO_INCOMPLETE && NumBytes > 0 && NumBytes < mBufferLength);
	if (bValidNotification) {
		memcpy(mBackBuffer, mBuffer, NumBytes);
		uint8* InfoBase = mBackBuffer;
		WCHAR RawFilename[256];
		do {
			FILE_NOTIFY_INFORMATION* NotifyInfo = (FILE_NOTIFY_INFORMATION*)InfoBase;
			if (NotifyInfo->Action == FILE_ACTION_MODIFIED && NotifyInfo->FileNameLength < 256) {
				const int32 Len = NotifyInfo->FileNameLength / sizeof(WCHAR);
				memcpy(RawFilename, NotifyInfo->FileName, NotifyInfo->FileNameLength);
				RawFilename[Len] = 0;
				FString filename = TCHAR_TO_UTF8(RawFilename);
				bool bLuafile = filename.RemoveFromEnd(TEXT(".lua"));
				if (bLuafile) {
					filename.ReplaceCharInline('\\', '.');
					LuaScriptMap.Add(FName(filename));
				}
			}
			if (NotifyInfo->NextEntryOffset == 0)
				break;
			InfoBase += NotifyInfo->NextEntryOffset;
		} while (true);
	}
	WatchScriptDirectorChange();
}
bool UGameLuaSubsystem::ReloadConfig()
{
	FString LoadDir = FPaths::ProjectContentDir() / TEXT("Table/BPConfig.ini");  //文件路径
	if (!FFileManagerGeneric::Get().FileExists(*LoadDir)) //判断是否存在文件
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
		// CDO还没有初始化完成
		return "";
	}

	if (!Class->ImplementsInterface(UUnLuaInterface::StaticClass()))
	{
		return "";
	}
	return IUnLuaInterface::Execute_GetModuleName(CDO);
}
#undef LOCTEXT_NAMESPACE