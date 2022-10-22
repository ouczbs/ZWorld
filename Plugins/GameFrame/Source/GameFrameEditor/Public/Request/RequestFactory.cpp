#include "RequestFactory.h"
#include "AssetTypeCategories.h"
#include "Request/RequestBlueprint.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "RequestFactory"


URequestFactory::URequestFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = URequestBlueprint::StaticClass();
}
UObject* URequestFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	// Make sure we are trying to factory a SM Blueprint, then create and init one
	check(Class->IsChildOf(SupportedClass));
	return FKismetEditorUtilities::CreateBlueprint(URequest::StaticClass(), InParent, Name, EBlueprintType::BPTYPE_Normal, URequestBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext);
}

UObject* URequestFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}


FString URequestFactory::GetDefaultNewAssetName() const
{
	return TEXT("GR_Request");
}
#undef LOCTEXT_NAMESPACE // "RequestFactory"