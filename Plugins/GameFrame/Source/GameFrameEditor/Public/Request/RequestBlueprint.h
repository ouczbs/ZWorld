

#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "RequestBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFRAMEEDITOR_API URequestBlueprint : public UBlueprint
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual bool SupportsInputEvents() const override{
		return true;
	};
};
