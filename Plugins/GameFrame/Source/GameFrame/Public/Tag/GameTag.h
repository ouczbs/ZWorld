
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameTag.generated.h"
/**
 * A single gameplay tag, which represents a hierarchical name of the form x.y that is registered in the GameplayTagsManager
 * You can filter the gameplay tags displayed in the editor using, meta = (Categories = "Tag1.Tag2.Tag3"))
 */
USTRUCT(BlueprintType)
struct GAMEFRAME_API FGameTag
{
	GENERATED_USTRUCT_BODY()

	/** Constructors */
	FGameTag()
	{
	}
    	/** Intentionally private so only the tag manager can use */
	FGameTag(const FString& TagString): Name(*TagString){
        TArray<FString> stringArray;
        TagString.ParseIntoArray(stringArray, TEXT("."), false);
        for(FString string : stringArray){
            TagNames.Add(*string);
        }
    }
	    	/** Intentionally private so only the tag manager can use */
	FORCEINLINE void Construct(const FString& TagString){
		Name = *TagString;
		TagNames.Reset();
        TArray<FString> stringArray;
        TagString.ParseIntoArray(stringArray, TEXT("."), false);
        for(FString string : stringArray){
            TagNames.Add(*string);
        }
    }
	/** Operators */
	FORCEINLINE bool operator==(const FGameTag& Other) const
	{
		return Name == Other.Name;
	}
	FORCEINLINE bool operator!=(const FGameTag& Other) const
	{
		return Name != Other.Name;
	}
	FORCEINLINE bool operator<(const FGameTag & Other) const
	{
		return Name.LexicalLess(Other.Name);
	}
	/** Returns whether the tag is valid or not; Invalid tags are set to NAME_None and do not exist in the game-specific global dictionary */
	FORCEINLINE bool IsValid() const
	{
		return (Name != NAME_None);
	}

	/** Used so we can have a TMap of this struct */
	FORCEINLINE friend uint32 GetTypeHash(const FGameTag& Tag)
	{
		return ::GetTypeHash(Tag.Name);
	}

	/** Displays gameplay tag as a string for blueprint graph usage */
	FORCEINLINE FString ToString() const
	{
		return Name.ToString();
	}
	FORCEINLINE bool Contains(const FGameTag& Tag) const
	{
        int len =  TagNames.Num() - Tag.TagNames.Num();
        for(int i = 0 ; i < len; i++ ){
            //if (equal(Tag.TagNames.begin(), Tag.TagNames.end(), TagNames.begin() + i)) {
              //  return true;
            //}
        }
		return false;
	}

public:
	/** This Tags Name */
	UPROPERTY(EditAnyWhere)
	FName Name;
	UPROPERTY(VisibleAnywhere)
	TArray<FName> TagNames;
};

/** A Tag Container holds a collection of FGameTags, tags are included explicitly by adding them, and implicitly from adding child tags */
USTRUCT(BlueprintType)
struct GAMEFRAME_API FGameTagContainer{
    GENERATED_USTRUCT_BODY()

	/** Constructors */
	FGameTagContainer()
	{
	}

	FGameTagContainer(const FGameTagContainer& Other)
	{
		*this = Other;
	}
    FGameTagContainer(const FGameTag& Tag)
	{
		AddTag(Tag);
	}

	FORCEINLINE void AddTag(const FGameTag& Tag) 
	{
		auto p_count = GameTagMap.Find(Tag);
		int32 count = 0;
		if (p_count) {
			count = *p_count + 1;
		}
        GameTagMap.Add(Tag , count);
	}
    FORCEINLINE void RemoveTag(const FGameTag& Tag , bool bForceRemove = false)
	{
        auto p_count = GameTagMap.Find(Tag);
		int32 count = 0;
        if(p_count){
			count = *p_count - 1;
        }
		if (count < 0 || bForceRemove) {
			GameTagMap.Remove(Tag);
		}
	}
    FORCEINLINE_DEBUGGABLE bool HasAny(const FGameTagContainer& ContainerToCheck) const
	{
		for (auto PairTarget : ContainerToCheck.GameTagMap)
		{
            for (auto PairSource : GameTagMap)
		    {
                if(PairSource.Key.Contains(PairTarget.Key)){
                    return true;
                }
            }
		}
		return false;
	}
    FORCEINLINE_DEBUGGABLE bool HasAll(const FGameTagContainer& ContainerToCheck) const
	{
        if(ContainerToCheck.GameTagMap.Num() == 0){
            return true;
        }
		for (auto PairTarget : ContainerToCheck.GameTagMap)
		{
            for (auto PairSource : GameTagMap)
		    {
                if(!PairSource.Key.Contains(PairTarget.Key)){
                    return false;
                }
            }
		}
        if(GameTagMap.Num() > 0){
            return true;
        }
		return false;
	}
public:
	UPROPERTY(EditAnywhere)
	TMap<FGameTag, int32> GameTagMap;
};