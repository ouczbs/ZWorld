// Copyright 2018-2020 X.D. Network Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "Socket.h"

#include "HAL/PlatformFilemanager.h"
#include "HAL/FileManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

class Socket;
class FJsonObject;
class FConvertJson2pb;

DECLARE_DELEGATE(FSendMessageEvent)

class Message
{
public:

	using LuaRcvPbcEvt = std::function<void(const std::string, int16 id)>;
	LuaRcvPbcEvt OnLuaRecvPbcMsg;

    explicit Message(const std::string &remote = "mmm.io:9876");
	~Message();

	void PostConnect();
	void PostDisconnect();

	void SendPbcMessage(const std::string& buffer, int id);

	void OnSendMessage();
    void OnReceiveMessage(std::vector<uint8_t> msg);
    void OnServerConnected(std::string remote);
    void OnServerDisconnected(std::string remote);
	
protected:
    void onSocket(Socket& s, int e, std::vector<uint8_t> b);
    
private:
    std::string _remote;
    std::vector<uint8_t> _buffer;
    std::unique_ptr<Socket> _socket;
};
