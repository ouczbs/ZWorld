// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MMOGameInstance.h"
#include "Unlua.h"
#include "LuaWrapper/CppBindingLibs.h"
void UMMOGameInstance::Init()
{
	Super::Init();
	//FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMMOGameInstance::BeginLoadingScreen);
	//FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMMOGameInstance::EndLoadingScreen);
}

void UMMOGameInstance::BeginLoadingScreen(const FString& MapName)
{
	UUserWidget* LoadingWidget = CreateWidget<UUserWidget>(this, LoadingWidgetClass);
	if (!LoadingWidget)
		return;
	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.MinimumLoadingScreenDisplayTime = MinimumLoadingScreenDisplayTime;
	LoadingScreen.WidgetLoadingScreen = LoadingWidget->TakeWidget();
	LoadingScreen.bAutoCompleteWhenLoadingCompletes = bAutoCompleteWhenLoadingCompletes;
	LoadingScreen.bMoviesAreSkippable = bMoviesAreSkippable;
	LoadingScreen.bWaitForManualStop = bWaitForManualStop;
	LoadingScreen.bAllowInEarlyStartup = bAllowInEarlyStartup;
	LoadingScreen.bAllowEngineTick = bAllowEngineTick;
	LoadingScreen.PlaybackType = PlaybackType;
	LoadingScreen.MoviePaths = MoviePaths;
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

void UMMOGameInstance::EndLoadingScreen(UWorld* LoadedWorld)
{
	
}

void UMMOGameInstance::Tick(float DeltaTime)
{
	ReceiveTick(DeltaTime);
}

void UMMOGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
	if (NewWorld) {
		OverrideWorldChanged(OldWorld, NewWorld);
		NewWorld->OnWorldBeginPlay.AddUObject(this, &UMMOGameInstance::BeginPlay);
	}
}
void UMMOGameInstance::BeginPlay() {
	ReceiveBeginPlay();
}
void UMMOGameInstance::OnStart()
{
	Super::OnStart();
	lua_State* L = UnLua::GetState();
	lua_register(L, "proto_send", proto::_send);
	OverrideInitGame();
}