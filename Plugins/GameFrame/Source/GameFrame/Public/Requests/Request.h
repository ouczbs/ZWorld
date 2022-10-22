#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Tag/RequestTag.h"
#include "Owner/GameOwner.h"
#include "Interface/PoolObjectInterface.h"
#include "Request.generated.h"

/*
* Entry -> Pending
* Pending | Active -> Active | Blocked | Canceled
*/
//必须添加BlueprintType标识
class UGameOwner;
UCLASS(Blueprintable)
class GAMEFRAME_API URequest : public URequestTag , public IPoolObjectInterface
{
    GENERATED_BODY()
public:
    virtual UWorld* GetWorld() const override
    {
        return GWorld;
    }
public:
    void MarkState(ERequestState NewState){
        State = NewState;
    }
    UFUNCTION(BlueprintCallable, Category="Request State")
    bool IsSuccessed(){
        return bIsSuccessed;
    }
    UFUNCTION(BlueprintCallable, Category="Request State")
    ERequestState GetState(){
        return State;
    }
    UFUNCTION(BlueprintCallable, Category="Request Owner")
    UGameOwner* GetOwner(){
        return Owner;
    }
    FName& GetName(){
        return Name;
    }
    void InitRequest(UGameOwner* _Owner , FName& _Name){
        Owner = _Owner;
        Name = _Name;
    }
    UFUNCTION(BlueprintCallable, Category="Request Owner")
    void PushRequest(){
        Owner->PushRequest(this);
    }
    virtual void Start(){
        Owner->AddContainerTags(OwnerTags);
        OnStart();
    }
    virtual void Stop(){
        Owner->RemoveContainerTags(OwnerTags);
        OnStop();
    }
    virtual void Tick(float DeltaTime){
        OnTick(DeltaTime);
    }
    UFUNCTION(BlueprintImplementableEvent, Category="Request")
    void OnStart();
    UFUNCTION(BlueprintImplementableEvent, Category="Request")
    void OnTick(float DeltaTime);
    UFUNCTION(BlueprintImplementableEvent, Category="Request")
    void OnStop();
public:
    // virtual Interface
    UFUNCTION(BlueprintCallable, Category="Request")
    virtual ERequestState TryActiveRequest(){
        const FGameTagContainer& GameTags =  Owner->GetGameTags();
        return TryActiveTag(GameTags);
    }
private:
    UGameOwner* Owner;
    ERequestState State = ERequestState::Entry;
    bool bIsSuccessed = false;
    FName Name;
public:
    UPROPERTY(EditAnyWhere)
    bool IsOnly = true;
    UPROPERTY(EditAnyWhere)
    bool IsPersistence = true;
    UPROPERTY(EditAnyWhere, Category = Tags)
    FGameTagContainer OwnerTags;
};

