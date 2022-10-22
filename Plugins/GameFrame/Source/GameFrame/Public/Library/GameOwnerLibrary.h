

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameOwnerLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFRAME_API UGameOwnerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameLibrary")
	static UGameInstanceSubsystem* GetGameSubsystem(TSubclassOf<UGameInstanceSubsystem> Class)
	{
		if (const UGameInstance* GameInstance = GWorld->GetGameInstance())
		{
			return GameInstance->GetSubsystemBase(Class);
		}
		return nullptr;
	}
};
