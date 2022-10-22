#pragma once
#include "GameTag.h"
#include "RequestTag.generated.h"
UENUM(BlueprintType)
enum class ERequestState : uint8
{
	Entry,
    Pending,
	Active,   
	Blocked,   
    Canceled, 
};
UCLASS(Blueprintable)
class URequestTag : public UObject
{ 
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Tags")
	void AddRequiredTag(FGameTag& Tag){
        RequiredTags.AddTag(Tag);
    };
    UFUNCTION(BlueprintCallable, Category="Tags")
    void RemoveRequiredTag(FGameTag& Tag){
        RequiredTags.RemoveTag(Tag);
    };
    UFUNCTION(BlueprintCallable, Category="Tags")
    void AddBlockedTag(FGameTag& Tag){
        BlockedTags.AddTag(Tag);
    };
    UFUNCTION(BlueprintCallable, Category="Tags")
    void RemoveBlockedTag(FGameTag& Tag){
        BlockedTags.RemoveTag(Tag);
    };
    UFUNCTION(BlueprintCallable, Category="Tags")
    void AddCanceledTag(FGameTag& Tag){
        CanceledTags.AddTag(Tag);
    };
    UFUNCTION(BlueprintCallable, Category="Tags")
    void RemoveCanceledTag(FGameTag& Tag){
        CanceledTags.RemoveTag(Tag);
    };
    UFUNCTION(BlueprintCallable, Category="Tags")
    ERequestState TryActiveTag(const FGameTagContainer& GameTags){
        if (!GameTags.HasAll(RequiredTags) || GameTags.HasAny(CanceledTags))
        {
            return ERequestState::Canceled;
        }
        if (GameTags.HasAny(BlockedTags))
        {
            return ERequestState::Blocked;
        }
        return ERequestState::Active;
    };
protected:
    UPROPERTY(EditDefaultsOnly, Category = Tags)
    FGameTagContainer RequiredTags;// if can't meet , so the request should to be canceled. 
	UPROPERTY(EditDefaultsOnly, Category = Tags)
    FGameTagContainer BlockedTags;//if can't meet , so the request should to be blocked. no execute but request still active
    UPROPERTY(EditDefaultsOnly, Category = Tags)
    FGameTagContainer CanceledTags;
};

/*
 push request();

*/