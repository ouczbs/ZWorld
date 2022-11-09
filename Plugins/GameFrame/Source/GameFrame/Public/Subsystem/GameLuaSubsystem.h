// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define ENABLE_HOT_RELOAD_LUA_SCRIPTS
#include "CoreMinimal.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/PreWindowsApi.h"
#include <windows.h> //冲突头文件
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

//#include "Proto/DataConfig.pb.h"
#include "Proto/DataConfig.pb.h"
#include "LuaModuleLocator.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameLuaSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFRAME_API UGameLuaSubsystem : public UGameInstanceSubsystem , public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return !IsTemplate(); }//不是CDO才Tick
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UMyScoreSubsystem, STATGROUP_Tickables); }

	UFUNCTION(BlueprintCallable, Category = "LuaSystem")
	bool ReloadConfig();
	UFUNCTION(BlueprintCallable, Category = "LuaSystem")
	FString FindLuaModule(FString& Name);

	void WatchScriptDirectorChange();
	void ProcessChange(uint32 Error, uint32 NumBytes);
	static UGameLuaSubsystem* GetSystem() {
		return LuaSystem;
	}
private:
	HANDLE mDirectoryHandle;
	uint8* mBuffer;
	uint8* mBackBuffer;
	uint32 mBufferLength;

	TSet<FName> LuaScriptMap;

	TMap<FName, FString> LuaBPMap;
	static UGameLuaSubsystem* LuaSystem;
};

UCLASS()
class GAMEFRAME_API ULuaModuleLocator_ByConfig : public ULuaModuleLocator
{
	GENERATED_BODY()
public:
	virtual FString Locate(const UObject* Object) override;
};