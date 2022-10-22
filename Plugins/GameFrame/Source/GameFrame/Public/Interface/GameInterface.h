#pragma once

#include "UObject/Interface.h"
#include "GameInterface.generated.h"

/**
 * Interface for support pool
 */
UINTERFACE()
class GAMEFRAME_API UGameInterface : public UInterface
{
    GENERATED_BODY()
};
class UGameOwner;
class GAMEFRAME_API IGameInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent)
    UGameOwner* GetGameOwner();
};
