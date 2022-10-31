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
   virtual void OnSpawn(){};
   virtual void OnUnspawn(){};
};
