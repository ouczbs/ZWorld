// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetWork/Message.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameMessageSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ZWORLD_API UGameMessageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "C++ API")
	void Connect(const FString& Host);
	UFUNCTION(BlueprintCallable, Category = "C++ API")
	void Disconnect();

	UFUNCTION(BlueprintImplementableEvent, Category = "Override C++")
	void OverrideDisconncet();

	void SendMessage(const std::string& msg, int id);

	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;

	static UGameMessageSubsystem* GetInstance() {
		return sInstance;
	};
protected:
	TSharedPtr<Message> message;
	static UGameMessageSubsystem* sInstance;
};
