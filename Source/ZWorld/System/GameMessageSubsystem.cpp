// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GameMessageSubsystem.h"
#include "Unlua.h"
UGameMessageSubsystem* UGameMessageSubsystem::sInstance = nullptr;
void UGameMessageSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	sInstance = this;
}
void UGameMessageSubsystem::Deinitialize() {
	sInstance = nullptr;
}
void UGameMessageSubsystem::Disconnect()
{
	message->PostDisconnect();
	OverrideDisconncet();
}

void UGameMessageSubsystem::Connect(const FString& Host)
{
	UE_LOG(LogTemp, Display, TEXT("Connect To Host [%s]."), *Host);
	message = MakeShareable(new Message(std::string(TCHAR_TO_UTF8(*Host))));
	message->OnLuaRecvPbcMsg = [this](const std::string& content, int16 id) {
		AsyncTask(ENamedThreads::GameThread, [content, id]() {
			lua_State* L = UnLua::GetState();
		UE_LOG(LogTemp, Display, TEXT("Test Connect, binary length [%i]."), content.length());
		UE_LOG(LogTemp, Display, TEXT("Test Connect, binary stream [%s]."), *FString(content.c_str()));
		if (L) {
			lua_getglobal(L, "Pbc");
			lua_getfield(L, -1, "recv");
			lua_pushlstring(L, content.c_str(), content.size());
			lua_pushnumber(L, id);
			if (lua_pcall(L, 2, 0, 0) != 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Error while executing pbc: %s"), *FString(lua_tostring(L, -1)));
				lua_settop(L, 0);
				return;
			}
			lua_settop(L, 0);
		}
			});
	};
	message->PostConnect();
}
void UGameMessageSubsystem::SendMessage(const std::string& msg, int id) {
	if (message)
		message->SendPbcMessage(msg, id);
}