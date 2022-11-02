// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIStruct.h"
#include "UnLua.h"

int stackDump(lua_State* L)
{
    int i = 0;
    int top = lua_gettop(L);
    UE_LOG(LogTemp, Warning, TEXT("stackDump size is %d"), top);
    for (i = 1; i <= top; ++i)
    {
        int t = lua_type(L, i);
        switch (t)
        {
        case LUA_TSTRING:         // strings
            UE_LOG(LogTemp, Warning, TEXT("%d is strings %s"), i , lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:        // bool
            UE_LOG(LogTemp, Warning, TEXT("%d is boolean %s"), i, lua_toboolean(L, i) ? "true" : "false");;
            break;
        case LUA_TNUMBER:         // number
            UE_LOG(LogTemp, Warning, TEXT("%d is number %d"), i, lua_tonumber(L, i));
            break;
        default:                  // other values
            UE_LOG(LogTemp, Warning, TEXT("%d is table %d"), i, lua_typename(L, t));
            break;
        }
        std::cout << " ";
    }
    std::cout << std::endl;
    return 1;
}

int ULuaObject::SetData(lua_State* L)
{
    if (ref != ELuaRef::REF_NULL) {
        luaL_unref(L, LUA_REGISTRYINDEX, ref);
    }
    ref = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}

int ULuaObject::GetData(lua_State* L)
{
    if (ref == LUA_REFNIL) 
        lua_pushnil(L);
    else
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    return 1;
}

int ULuaObject::TestGetData(ULuaObject* obj)
{
    lua_State* L = UnLua::GetState();
    stackDump(L);
    if (obj) {
        obj->GetData(L);
    }
    return 0;
}

void ULuaObject::OnUnspawn()
{
    if (ref != ELuaRef::REF_NULL) {
        lua_State* L = UnLua::GetState();
        luaL_unref(L, LUA_REGISTRYINDEX, ref);
    }
    ref = ELuaRef::REF_NULL;
}
