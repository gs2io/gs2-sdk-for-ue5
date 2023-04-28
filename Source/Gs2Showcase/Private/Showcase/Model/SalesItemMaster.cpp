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

#include "Showcase/Model/SalesItemMaster.h"

namespace Gs2::Showcase::Model
{
    FSalesItemMaster::FSalesItemMaster():
        SalesItemIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ConsumeActionsValue(nullptr),
        AcquireActionsValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FSalesItemMaster::FSalesItemMaster(
        const FSalesItemMaster& From
    ):
        SalesItemIdValue(From.SalesItemIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ConsumeActionsValue(From.ConsumeActionsValue),
        AcquireActionsValue(From.AcquireActionsValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FSalesItemMaster> FSalesItemMaster::WithSalesItemId(
        const TOptional<FString> SalesItemId
    )
    {
        this->SalesItemIdValue = SalesItemId;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemMaster> FSalesItemMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemMaster> FSalesItemMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemMaster> FSalesItemMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemMaster> FSalesItemMaster::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemMaster> FSalesItemMaster::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemMaster> FSalesItemMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemMaster> FSalesItemMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FSalesItemMaster::GetSalesItemId() const
    {
        return SalesItemIdValue;
    }
    TOptional<FString> FSalesItemMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FSalesItemMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FSalesItemMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FSalesItemMaster::GetConsumeActions() const
    {
        return ConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FSalesItemMaster::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }
    TOptional<int64> FSalesItemMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FSalesItemMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FSalesItemMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FSalesItemMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FSalesItemMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):salesItem:(?<salesItemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSalesItemMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):salesItem:(?<salesItemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSalesItemMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):salesItem:(?<salesItemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSalesItemMaster::GetSalesItemNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):showcase:(?<namespaceName>.+):salesItem:(?<salesItemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSalesItemMaster> FSalesItemMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSalesItemMaster>()
            ->WithSalesItemId(Data->HasField("salesItemId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("salesItemId", v))
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
            ->WithConsumeActions(Data->HasField("consumeActions") ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("consumeActions") && Data->HasTypedField<EJson::Array>("consumeActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("consumeActions"))
                        {
                            v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FConsumeActionPtr>>())
            ->WithAcquireActions(Data->HasField("acquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("acquireActions") && Data->HasTypedField<EJson::Array>("acquireActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("acquireActions"))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
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

    TSharedPtr<FJsonObject> FSalesItemMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SalesItemIdValue.IsSet())
        {
            JsonRootObject->SetStringField("salesItemId", SalesItemIdValue.GetValue());
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
        if (ConsumeActionsValue != nullptr && ConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("consumeActions", v);
        }
        if (AcquireActionsValue != nullptr && AcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActions", v);
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

    FString FSalesItemMaster::TypeName = "SalesItemMaster";
}