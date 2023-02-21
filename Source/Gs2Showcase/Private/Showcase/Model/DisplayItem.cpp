/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Showcase/Model/DisplayItem.h"

namespace Gs2::Showcase::Model
{
    FDisplayItem::FDisplayItem():
        DisplayItemIdValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        SalesItemValue(nullptr),
        SalesItemGroupValue(nullptr),
        SalesPeriodEventIdValue(TOptional<FString>())
    {
    }

    FDisplayItem::FDisplayItem(
        const FDisplayItem& From
    ):
        DisplayItemIdValue(From.DisplayItemIdValue),
        TypeValue(From.TypeValue),
        SalesItemValue(From.SalesItemValue),
        SalesItemGroupValue(From.SalesItemGroupValue),
        SalesPeriodEventIdValue(From.SalesPeriodEventIdValue)
    {
    }

    TSharedPtr<FDisplayItem> FDisplayItem::WithDisplayItemId(
        const TOptional<FString> DisplayItemId
    )
    {
        this->DisplayItemIdValue = DisplayItemId;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItem> FDisplayItem::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItem> FDisplayItem::WithSalesItem(
        const TSharedPtr<FSalesItem> SalesItem
    )
    {
        this->SalesItemValue = SalesItem;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItem> FDisplayItem::WithSalesItemGroup(
        const TSharedPtr<FSalesItemGroup> SalesItemGroup
    )
    {
        this->SalesItemGroupValue = SalesItemGroup;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItem> FDisplayItem::WithSalesPeriodEventId(
        const TOptional<FString> SalesPeriodEventId
    )
    {
        this->SalesPeriodEventIdValue = SalesPeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FDisplayItem::GetDisplayItemId() const
    {
        return DisplayItemIdValue;
    }
    TOptional<FString> FDisplayItem::GetType() const
    {
        return TypeValue;
    }
    TSharedPtr<FSalesItem> FDisplayItem::GetSalesItem() const
    {
        return SalesItemValue;
    }
    TSharedPtr<FSalesItemGroup> FDisplayItem::GetSalesItemGroup() const
    {
        return SalesItemGroupValue;
    }
    TOptional<FString> FDisplayItem::GetSalesPeriodEventId() const
    {
        return SalesPeriodEventIdValue;
    }

    TSharedPtr<FDisplayItem> FDisplayItem::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDisplayItem>()
            ->WithDisplayItemId(Data->HasField("displayItemId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("displayItemId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField("type") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("type", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSalesItem(Data->HasField("salesItem") ? [Data]() -> Model::FSalesItemPtr
                {
                    if (Data->HasTypedField<EJson::Null>("salesItem"))
                    {
                        return nullptr;
                    }
                    return Model::FSalesItem::FromJson(Data->GetObjectField("salesItem"));
                 }() : nullptr)
            ->WithSalesItemGroup(Data->HasField("salesItemGroup") ? [Data]() -> Model::FSalesItemGroupPtr
                {
                    if (Data->HasTypedField<EJson::Null>("salesItemGroup"))
                    {
                        return nullptr;
                    }
                    return Model::FSalesItemGroup::FromJson(Data->GetObjectField("salesItemGroup"));
                 }() : nullptr)
            ->WithSalesPeriodEventId(Data->HasField("salesPeriodEventId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("salesPeriodEventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDisplayItem::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DisplayItemIdValue.IsSet())
        {
            JsonRootObject->SetStringField("displayItemId", DisplayItemIdValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (SalesItemValue != nullptr && SalesItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("salesItem", SalesItemValue->ToJson());
        }
        if (SalesItemGroupValue != nullptr && SalesItemGroupValue.IsValid())
        {
            JsonRootObject->SetObjectField("salesItemGroup", SalesItemGroupValue->ToJson());
        }
        if (SalesPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("salesPeriodEventId", SalesPeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FDisplayItem::TypeName = "DisplayItem";
}