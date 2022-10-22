#pragma once
#include "Requests/Request.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Tag/RequestTag.h"
#include "Owner/GameOwner.h"
#include "Interface/PoolObjectInterface.h"
#include "DelegateRequest.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTickDelegate, float , DeltaTime);

UCLASS(Blueprintable)
class GAMEFRAME_API UDelegateRequest : public URequest
{
    GENERATED_BODY()

public:
    virtual void Tick(float DeltaTime){
        if(OnTickDelegate.IsBound()){
            OnTickDelegate.Execute(DeltaTime);
        }
    }
private:
    UPROPERTY(EditAnywhere)
    FOnTickDelegate OnTickDelegate;
};
