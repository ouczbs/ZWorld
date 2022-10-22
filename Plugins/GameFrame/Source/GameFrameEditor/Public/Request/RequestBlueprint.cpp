


#include "RequestBlueprint.h"
#include "Requests/Request.h"
#define LOCTEXT_NAMESPACE "RequestBlueprint"
URequestBlueprint::URequestBlueprint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BlueprintType = BPTYPE_Normal;
	BlueprintCategory = "Request";
	ParentClass = URequest::StaticClass();
}
#undef LOCTEXT_NAMESPACE