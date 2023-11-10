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

#include "Showcase/Model/DisplayItemMaster.h"

namespace Gs2::Showcase::Model
{
    FDisplayItemMaster::FDisplayItemMaster():
        DisplayItemIdValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        SalesItemNameValue(TOptional<FString>()),
        SalesItemGroupNameValue(TOptional<FString>()),
        SalesPeriodEventIdValue(TOptional<FString>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FDisplayItemMaster::FDisplayItemMaster(
        const FDisplayItemMaster& From
    ):
        DisplayItemIdValue(From.DisplayItemIdValue),
        TypeValue(From.TypeValue),
        SalesItemNameValue(From.SalesItemNameValue),
        SalesItemGroupNameValue(From.SalesItemGroupNameValue),
        SalesPeriodEventIdValue(From.SalesPeriodEventIdValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FDisplayItemMaster> FDisplayItemMaster::WithDisplayItemId(
        const TOptional<FString> DisplayItemId
    )
    {
        this->DisplayItemIdValue = DisplayItemId;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItemMaster> FDisplayItemMaster::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItemMaster> FDisplayItemMaster::WithSalesItemName(
        const TOptional<FString> SalesItemName
    )
    {
        this->SalesItemNameValue = SalesItemName;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItemMaster> FDisplayItemMaster::WithSalesItemGroupName(
        const TOptional<FString> SalesItemGroupName
    )
    {
        this->SalesItemGroupNameValue = SalesItemGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItemMaster> FDisplayItemMaster::WithSalesPeriodEventId(
        const TOptional<FString> SalesPeriodEventId
    )
    {
        this->SalesPeriodEventIdValue = SalesPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FDisplayItemMaster> FDisplayItemMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FDisplayItemMaster::GetDisplayItemId() const
    {
        return DisplayItemIdValue;
    }
    TOptional<FString> FDisplayItemMaster::GetType() const
    {
        return TypeValue;
    }
    TOptional<FString> FDisplayItemMaster::GetSalesItemName() const
    {
        return SalesItemNameValue;
    }
    TOptional<FString> FDisplayItemMaster::GetSalesItemGroupName() const
    {
        return SalesItemGroupNameValue;
    }
    TOptional<FString> FDisplayItemMaster::GetSalesPeriodEventId() const
    {
        return SalesPeriodEventIdValue;
    }
    TOptional<int64> FDisplayItemMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FDisplayItemMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TSharedPtr<FDisplayItemMaster> FDisplayItemMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDisplayItemMaster>()
            ->WithDisplayItemId(Data->HasField("displayItemId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("displayItemId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField("type") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("type", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSalesItemName(Data->HasField("salesItemName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("salesItemName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSalesItemGroupName(Data->HasField("salesItemGroupName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("salesItemGroupName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSalesPeriodEventId(Data->HasField("salesPeriodEventId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("salesPeriodEventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FDisplayItemMaster::ToJson() const
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
        if (SalesItemNameValue.IsSet())
        {
            JsonRootObject->SetStringField("salesItemName", SalesItemNameValue.GetValue());
        }
        if (SalesItemGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField("salesItemGroupName", SalesItemGroupNameValue.GetValue());
        }
        if (SalesPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("salesPeriodEventId", SalesPeriodEventIdValue.GetValue());
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FDisplayItemMaster::TypeName = "DisplayItemMaster";
}