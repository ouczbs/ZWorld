// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interface/PoolObjectInterface.h"
#include "UIStruct.generated.h"

enum ELuaRef
{
	REF_NIL = -1,//LUA_NILREF
	REF_NULL= -2,//LUA_NOREF
};
UCLASS(BlueprintType)
class GAMEFRAME_API ULuaObject : public UObject, public IPoolObjectInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "LuaLibrary")
	int SetData();
	UFUNCTION(BlueprintCallable, Category = "LuaLibrary")
	int GetData();

	virtual void OnUnspawn() override;
private:
	int ref = ELuaRef::REF_NULL;
};

UCLASS(BlueprintType)
class GAMEFRAME_API ULuaUIEntry : public ULuaObject
{
	GENERATED_BODY()
};