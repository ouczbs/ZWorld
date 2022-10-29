// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Proto/DataConfig.pb.h"
#include "Proto/DataConfig.pb.h"
#include "LuaModuleLocator.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameLuaSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFRAME_API UGameLuaSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;

	UFUNCTION(BlueprintCallable, Category = "LuaSystem")
	bool ReloadConfig();
	bool ReloadTestConfig();
	UFUNCTION(BlueprintCallable, Category = "LuaSystem")
	FString FindLuaModule(FString& Name);

	static UGameLuaSubsystem* GetSystem() {
		return LuaSystem;
	}
private:
	pb::BPConfig mConfig;
	static UGameLuaSubsystem* LuaSystem;
};

UCLASS()
class GAMEFRAME_API ULuaModuleLocator_ByConfig : public ULuaModuleLocator
{
	GENERATED_BODY()
public:
	virtual FString Locate(const UObject* Object) override;

private:
	TMap<FName, FString> Cache;
};