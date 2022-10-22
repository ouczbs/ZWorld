

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GamePoolSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFRAME_API USubObjectPool : public UObject
{
	GENERATED_BODY()
public:
	UObject* Spawn();
	void Unspawn(UObject* Object);
	UClass* ObjectClass;
private:
	UPROPERTY()
	TArray<UObject*> ObjectsPool;
};

UCLASS()
class GAMEFRAME_API UGamePoolSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "GamePool")
		UObject* Spawn(UClass* Class);
	UFUNCTION(BlueprintCallable, Category = "GamePool")
		void Unspawn(UObject* Object);
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;
private:
	UPROPERTY()
	TMap<FName, USubObjectPool*> ObjectPoolMap;
};
