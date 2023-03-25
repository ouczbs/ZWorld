// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"
#include "Engine/GameInstance.h"
#include "MMOGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ZWORLD_API UMMOGameInstance : public UGameInstance , public FTickableGameObject
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingWin")
        TSubclassOf<UUserWidget>  LoadingWidgetClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingWin")
    TArray<FString> MoviePaths;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingWin")
	float MinimumLoadingScreenDisplayTime = 10.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingWin")
	bool bAutoCompleteWhenLoadingCompletes = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingWin")
	bool bMoviesAreSkippable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingWin")
	bool bWaitForManualStop = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingWin")
	bool bAllowInEarlyStartup = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingWin")
	bool bAllowEngineTick = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingWin")
		TEnumAsByte<EMoviePlaybackType> PlaybackType = EMoviePlaybackType::MT_Normal;

    virtual void Init() override;
    void BeginLoadingScreen(const FString& MapName);
    void EndLoadingScreen(UWorld* LoadedWorld);

public:
    virtual TStatId GetStatId() const override { return Super::GetStatID(); }
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override
    {
        if (!GetWorld())
            return false;
        return GetWorld()->HasBegunPlay();
    }
	void BeginPlay();
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveBeginPlay();
public:
	virtual void OnStart() override;
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick"))
		void ReceiveTick(float DeltaSeconds);
	UFUNCTION(BlueprintImplementableEvent, Category = "Override C++")
		void OverrideWorldChanged(UWorld* OldWorld, UWorld* NewWorld);

	UFUNCTION(BlueprintImplementableEvent, Category = "Override C++")
	void OverrideInitGame();
};
