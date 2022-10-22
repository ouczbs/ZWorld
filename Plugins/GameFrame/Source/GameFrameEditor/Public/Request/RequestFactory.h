

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "RequestFactory.generated.h"

/**
 * 
 */
UCLASS()
class URequestFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

public:
	// UFactory
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context,
	FFeedbackContext* Warn, FName CallingContext) override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context,
	FFeedbackContext* Warn) override;
	virtual FString GetDefaultNewAssetName() const override;
	// ~UFactory
};
