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
struct lua_State;
UCLASS(BlueprintType)
class GAMEFRAME_API ULuaObject : public UObject, public IPoolObjectInterface
{
	GENERATED_BODY()

public:
	int SetData(lua_State* L);
	int GetData(lua_State* L);

	UFUNCTION(BlueprintCallable, Category = "LuaLibrary")
	int TestGetData(ULuaObject* obj);
	virtual void OnUnspawn() override;
private:
	int ref = ELuaRef::REF_NULL;
};
int stackDump(lua_State* L);
UCLASS(BlueprintType)
class GAMEFRAME_API ULuaUIEntry : public ULuaObject
{
	GENERATED_BODY()
};