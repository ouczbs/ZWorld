#pragma once

#include "UObject/Interface.h"
#include "PoolObjectInterface.generated.h"

/**
 * Interface for support pool
 */
UINTERFACE()
class GAMEFRAME_API UPoolObjectInterface : public UInterface
{
    GENERATED_BODY()
};

class GAMEFRAME_API IPoolObjectInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent)
    void OnSpawn();
    UFUNCTION(BlueprintNativeEvent)
    void OnUnspawn();
};
