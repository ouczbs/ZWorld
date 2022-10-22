

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameOwnerSubsystem.generated.h"

/**
 * 
 */
class UGamePoolSubsystem;
class UGameOwner;
class URequest;
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(URequest*, FInterfaceSpawnRequest, FName , Name);
UCLASS(abstract, Blueprintable, BlueprintType)
class GAMEFRAME_API UGameOwnerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;
	UFUNCTION(BlueprintImplementableEvent)
		void OnInitialize();
	UFUNCTION(BlueprintImplementableEvent)
		void OnDeinitialize();
    UFUNCTION(BlueprintCallable, Category = "GameOwner")
	void Tick(float DeltaTime);
    UFUNCTION(BlueprintCallable, Category = "GameOwner")
	UGameOwner* SpawnGameOwner();
    UFUNCTION(BlueprintCallable, Category = "GameOwner")
	URequest* SpawnRequest(FName Name);
private:
    UPROPERTY(EditAnywhere)
    FInterfaceSpawnRequest InterfaceSpawnRequest;
	UPROPERTY(VisibleAnywhere)
    TArray<UGameOwner *> GameOwners;
};
