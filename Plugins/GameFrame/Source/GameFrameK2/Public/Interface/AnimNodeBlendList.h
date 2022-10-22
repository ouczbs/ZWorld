#pragma once

#include "UObject/Interface.h"
#include "AnimNodeBlendList.generated.h"

/**
 * Interface for support pool
 */
UINTERFACE()
class  UAnimNodeBlendList : public UInterface
{
    GENERATED_BODY()
};
class UEdGraphPin;
class  IAnimNodeBlendList
{
    GENERATED_BODY()

public:
    virtual void AddPinToBlend(){};
    virtual void RemovePinFromBlend(UEdGraphPin* Pin){};
};
