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

#include "Showcase/Model/SalesItemGroupMaster.h"

namespace Gs2::Showcase::Model
{
    FSalesItemGroupMaster::FSalesItemGroupMaster():
        SalesItemGroupIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        SalesItemNamesValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FSalesItemGroupMaster::FSalesItemGroupMaster(
        const FSalesItemGroupMaster& From
    ):
        SalesItemGroupIdValue(From.SalesItemGroupIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        SalesItemNamesValue(From.SalesItemNamesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FSalesItemGroupMaster> FSalesItemGroupMaster::WithSalesItemGroupId(
        const TOptional<FString> SalesItemGroupId
    )
    {
        this->SalesItemGroupIdValue = SalesItemGroupId;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemGroupMaster> FSalesItemGroupMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemGroupMaster> FSalesItemGroupMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemGroupMaster> FSalesItemGroupMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemGroupMaster> FSalesItemGroupMaster::WithSalesItemNames(
        const TSharedPtr<TArray<FString>> SalesItemNames
    )
    {
        this->SalesItemNamesValue = SalesItemNames;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemGroupMaster> FSalesItemGroupMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemGroupMaster> FSalesItemGroupMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FSalesItemGroupMaster::GetSalesItemGroupId() const
    {
        return SalesItemGroupIdValue;
    }
    TOptional<FString> FSalesItemGroupMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FSalesItemGroupMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FSalesItemGroupMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<FString>> FSalesItemGroupMaster::GetSalesItemNames() const
    {
        return SalesItemNamesValue;
    }
    TOptional<int64> FSalesItemGroupMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FSalesItemGroupMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FSalesItemGroupMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FSalesItemGroupMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FSalesItemGroupMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):salesItemGroup:(?<salesItemGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSalesItemGroupMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):salesItemGroup:(?<salesItemGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSalesItemGroupMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):salesItemGroup:(?<salesItemGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSalesItemGroupMaster::GetSalesItemGroupNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):salesItemGroup:(?<salesItemGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSalesItemGroupMaster> FSalesItemGroupMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSalesItemGroupMaster>()
            ->WithSalesItemGroupId(Data->HasField("salesItemGroupId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("salesItemGroupId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSalesItemNames(Data->HasField("salesItemNames") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("salesItemNames") && Data->HasTypedField<EJson::Array>("salesItemNames"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("salesItemNames"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FSalesItemGroupMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SalesItemGroupIdValue.IsSet())
        {
            JsonRootObject->SetStringField("salesItemGroupId", SalesItemGroupIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (SalesItemNamesValue != nullptr && SalesItemNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SalesItemNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("salesItemNames", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FSalesItemGroupMaster::TypeName = "SalesItemGroupMaster";
}