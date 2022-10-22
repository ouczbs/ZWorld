


#include "Subsystem/GameTableSubsystem.h"
#include "Engine/DataTable.h"

void UGameTableSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
    OnInitialize();
}
void UGameTableSubsystem::Deinitialize() {
    OnDeinitialize();
}
bool UGameTableSubsystem::GetDataTableRow(UDataTable* Table, FName RowName, FStructTableBase& OutRow) {
	bool bFoundRow = false;
    void* OutRowPtr = (void*)&OutRow;
	if (Table && OutRowPtr)
	{
		void* RowPtr = Table->FindRowUnchecked(RowName);
		if (RowPtr != nullptr)
		{
			const UScriptStruct* StructType = Table->GetRowStruct();
			if (StructType)
			{
				StructType->CopyScriptStruct(OutRowPtr, RowPtr);
				bFoundRow = true;
			}
		}
	}

	return bFoundRow;
}
template <class T>
void UGameTableSubsystem::GetDataTableRowMap(const UDataTable* DataTable ,TMap<FName, T*>& ResultMap){
    const UScriptStruct* RowStruct = DataTable->GetRowStruct();
    if (RowStruct == nullptr)
    {
        //UE_LOG(LogDataTable, Error, TEXT("UDataTable::GetAllRows : DataTable '%s' has no RowStruct specified (%s)."), *GetPathName(), ContextString);
    }
    else if (!RowStruct->IsChildOf(T::StaticStruct()))
    {
        //UE_LOG(LogDataTable, Error, TEXT("UDataTable::GetAllRows : Incorrect type specified for DataTable '%s' (%s)."), *GetPathName(), ContextString);
    }
    else
    {
        for (TMap<FName, uint8*>::TConstIterator RowMapIter(DataTable->GetRowMap().CreateConstIterator()); RowMapIter; ++RowMapIter)
        {
            ResultMap.Add(RowMapIter.Key() , reinterpret_cast<T*>(RowMapIter.Value()));
        }
    }
}
