// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameTagCustomization.h"
#include "DetailLayoutBuilder.h"
#include "Tag/GameTag.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#define LOCTEXT_NAMESPACE "GameTagCustomization"

void FPropertyGameTagCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle = InStructPropertyHandle;
	FSimpleDelegate OnPropertyValueChanged = FSimpleDelegate::CreateSP(this, &FPropertyGameTagCustomization::OnPropertyValueChanged);
	StructPropertyHandle->SetOnPropertyValueChanged(OnPropertyValueChanged);
	auto NamePropertyHandle = InStructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameTag, Name));
	HeaderRow
	.NameContent()
	[
		StructPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MaxDesiredWidth(512)
	[
		NamePropertyHandle->CreatePropertyValueWidget()
	];
}

void FPropertyGameTagCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils){
	

}
void FPropertyGameTagCustomization::OnPropertyValueChanged()
{
	if (StructPropertyHandle.IsValid() && StructPropertyHandle->GetProperty())
	{
		TArray<void*> RawStructData;
		StructPropertyHandle->AccessRawData(RawStructData);
		if (RawStructData.Num() > 0)
		{
			FGameTag* GameTag = (FGameTag*)(RawStructData[0]);
			if (GameTag)
			{
				GameTag->Construct(GameTag->ToString());
			}			
		}
	}
}

void FPropertyGameTagContainerCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	HeaderRow
	.NameContent()
	[
		InStructPropertyHandle->CreatePropertyNameWidget()
	];
}

void FPropertyGameTagContainerCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils){
	

}
#undef LOCTEXT_NAMESPACE
