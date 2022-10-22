#pragma once
#include "GameTag.h"
#include "GameOwnerTag.generated.h"

UCLASS(Blueprintable)
class UGameOwnerTag : public UObject
{ 
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Tags")
	virtual void AddContainerTags(FGameTagContainer& Tags){
        for(auto It : Tags.GameTagMap){
			GameTags.AddTag(It.Key);
        }
    };
	UFUNCTION(BlueprintCallable, Category="Tags")
	virtual void RemoveContainerTags(FGameTagContainer& Tags){
		for (auto It : Tags.GameTagMap) {
			GameTags.RemoveTag(It.Key);
		}
    };
	UFUNCTION(BlueprintCallable, Category="Tags")
	virtual void AddGameTags(FGameTag& Tag){
        GameTags.AddTag(Tag);
    };
	UFUNCTION(BlueprintCallable, Category="Tags")
	virtual void RemoveGameTags(FGameTag& Tag){
         GameTags.RemoveTag(Tag);
    };
	const FGameTagContainer& GetGameTags(){
		return GameTags;
	}
protected:
    UPROPERTY(EditAnywhere)
	FGameTagContainer GameTags;
};
