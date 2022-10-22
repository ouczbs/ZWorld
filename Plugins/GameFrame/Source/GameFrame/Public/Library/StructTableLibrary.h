

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Serialization/Csv/CsvParser.h"
//#include "StructTableLibrary.generated.h"

/**
 * 
 */
class GAMEFRAME_API UStructTableLibrary
{
public:
    static void LoadTableHeaderRowNames(const TArray<const TCHAR*> Row , TArray<FName>& RowNames){
        for (int32 ColIdx = 0; ColIdx < Row.Num(); ++ColIdx)
        {
            FName Name = DataTableUtils::MakeValidName(Row[ColIdx]);
            RowNames.Add(Name);
        }
    }
    static UObject* LoadObjectClass(FName& VarName, FName& VarType){
        FString VarStr = VarName.ToString();
        TArray<FString> stringArray;
        VarStr.ParseIntoArray(stringArray, TEXT("."), false);
        if(stringArray.Num() != 2){
            VarType = VarName;
            return nullptr;
        }
        UClass* Class;
        UObject* ObjectClass;
        VarType = *stringArray[0];
        if (VarType == FName(TEXT("byte"))) {
            Class = UEnum::StaticClass();
        }
        else if (VarType == FName(TEXT("struct"))) {
            Class = UStruct::StaticClass();
        }
        else if (VarType == FName(TEXT("interface"))) {
            Class = UInterface::StaticClass();
        }
        else {
            Class = UObject::StaticClass();
        }
        ObjectClass = StaticFindObject(Class , ANY_PACKAGE, *stringArray[1]);
        if (ObjectClass == nullptr)
        {
            ObjectClass = StaticLoadObject(Class , nullptr, *stringArray[1]);
        }
        return ObjectClass;
    }
    static EPinContainerType LoadTableContainerType(FName& VarType){
        if (VarType == FName(TEXT("none"))) {
            return EPinContainerType::None;
        }
        else if (VarType == FName(TEXT("array"))) {
            return EPinContainerType::Array;
        }
        else if (VarType == FName(TEXT("map"))) {
            return EPinContainerType::Map;
        }
        else if (VarType == FName(TEXT("set"))) {
            return EPinContainerType::Set;
        }
        return EPinContainerType::None;
    }
	static TArray<FProperty*> GetTablePropertyArray(const TArray<FName>& Names, UStruct* InRowStruct)
    {
        TArray<FProperty*> ColumnProps;
        ColumnProps.AddZeroed( Names.Num() );
        for (int32 ColIdx = 0; ColIdx < Names.Num(); ++ColIdx)
        {
            FName PropName = Names[ColIdx];
            if(PropName == NAME_None)
            {
                continue;
            }
            FProperty* ColumnProp = FindFProperty<FProperty>(InRowStruct, PropName);
            // Didn't find a property with this name, problem..
            if(ColumnProps.Contains(ColumnProp) && DataTableUtils::IsSupportedTableProperty(ColumnProp))
            {
                ColumnProps[ColIdx] = ColumnProp;
            }
        }
        return ColumnProps;
    }
    static void CreateStructFromCSVString(FString FilePath ,FString TableDir = "/Game/Table/")
    {
        //FStructTableBase* StructBase = reinterpret_cast<FStructTableBase*>(RowData);
        const FString CSVData = FilePath;
        const FCsvParser Parser(CSVData);
	    const auto& Rows = Parser.GetRows();
        if(Rows.Num() < 5){return;}

        TArray<FName> DisplayNames , MemberNames , VarKeyTypes , VarValueTypes , VarContainerTypes;
        LoadTableHeaderRowNames(Rows[0], DisplayNames);
        LoadTableHeaderRowNames(Rows[1], MemberNames);
        LoadTableHeaderRowNames(Rows[2], VarKeyTypes);
        LoadTableHeaderRowNames(Rows[3], VarValueTypes);
        LoadTableHeaderRowNames(Rows[4], VarContainerTypes);

        FString StructName = DisplayNames[0].ToString();
        const FString PackageName = TableDir + StructName;
        UPackage* Package = CreatePackage(*PackageName);

        EObjectFlags Flags = RF_Public|RF_Standalone|RF_Transactional;
        UUserDefinedStruct* StructTable = FStructureEditorUtils::CreateUserDefinedStruct(Package, *StructName, Flags);

        TArray<FStructVariableDescription>& VarDescArray = FStructureEditorUtils::GetVarDesc(StructTable);
        FStructureEditorUtils::RemoveVariable(StructTable , VarDescArray[0].VarGuid);
        //PinCategory = ["bool" , "byte" , "int" , "int64" , "float" , "double" , "name" , "string" , "text" , "struct" , "interface", "object" , "class" , "softobject" , "softclass"];
        for (int32 ColIdx = 1; ColIdx < MemberNames.Num(); ++ColIdx)
        {
            FName KeyTypeName;
            UObject* KeyObjectClass = LoadObjectClass(VarKeyTypes[ColIdx] , KeyTypeName);

            FName ValueTypeName;
            UObject* ValueObjectClass = LoadObjectClass(VarValueTypes[ColIdx] , ValueTypeName);

            EPinContainerType ContainerType = LoadTableContainerType(VarContainerTypes[ColIdx]);

            FEdGraphTerminalType ValueType;
            ValueType.TerminalCategory = ValueTypeName;
            ValueType.TerminalSubCategoryObject = ValueObjectClass;

            bool isOk = FStructureEditorUtils::AddVariable( StructTable, FEdGraphPinType(KeyTypeName, NAME_None, KeyObjectClass, ContainerType, false, ValueType));
            if(isOk){
                auto VarDesc = VarDescArray[VarDescArray.Num() - 1];
                VarDesc.VarName = MemberNames[ColIdx];
                VarDesc.FriendlyName = DisplayNames[ColIdx].ToString();
            }
        }

        FString const PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
        UPackage::SavePackage(Package, NULL, RF_Standalone, *PackageFileName, GError, nullptr, false, true, SAVE_NoError);
    }
};
