#pragma once

#include "CoreMinimal.h"

#include "Tag/GameOwnerTag.h"
#include "Interface/PoolObjectInterface.h"
#include "GameOwner.generated.h"
/**
 * 
 */
class URequest;
class UAnimOwner;
UCLASS(Blueprintable)
class GAMEFRAME_API UGameOwner : public UGameOwnerTag, public IPoolObjectInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Owner")
	URequest* FindOrAddRequest(FName Name);
	void RemoveRequest(URequest* Request);
public:
 	// virtual Interface
	 UFUNCTION(BlueprintCallable, Category="Owner")
	virtual void TickRequest(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category="Owner")
	virtual bool PushRequest(URequest* Request);
private:
	TArray<URequest*>	ActiveRequests;
	TMap<FName, URequest*> AllRequests;
	//SubOwners
	UAnimOwner* AnimOwner;
};
