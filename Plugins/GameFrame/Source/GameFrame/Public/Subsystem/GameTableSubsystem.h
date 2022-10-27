

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameTableSubsystem.generated.h"
/**
 * Base class for all table row structs to inherit from.
 */
USTRUCT()
struct FStructTableBase : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY()
		int a;
	UPROPERTY()
		int b;
	FStructTableBase() { }
};
UCLASS(abstract, Blueprintable, BlueprintType)
class GAMEFRAME_API UGameTableSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;
	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialize();
	UFUNCTION(BlueprintImplementableEvent)
	void OnDeinitialize();

	UFUNCTION(BlueprintCallable, Category = "GameTable")
	static bool GetDataTableRow(UDataTable* Table, FName RowName, FStructTableBase& OutRow);
	UFUNCTION(BlueprintCallable, Category = "GameTable")
	static void SetSuperStruct(UDataTable* Table)
	{
		if (Table && Table->RowStruct) {
			auto RowStruct = Table->RowStruct;
			auto ScriptStruct = FTableRowBase::StaticStruct();
			if (!RowStruct->IsChildOf(ScriptStruct)){
				RowStruct->SetSuperStruct(ScriptStruct);
			}
			
		}
	}
	template <class T>
	static void GetDataTableRowMap(const UDataTable* DataTable ,TMap<FName, T*>& ResultMap);
};
