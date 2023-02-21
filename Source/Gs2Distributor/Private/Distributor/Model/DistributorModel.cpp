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

#include "Distributor/Model/DistributorModel.h"

namespace Gs2::Distributor::Model
{
    FDistributorModel::FDistributorModel():
        DistributorModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        InboxNamespaceIdValue(TOptional<FString>()),
        WhiteListTargetIdsValue(nullptr)
    {
    }

    FDistributorModel::FDistributorModel(
        const FDistributorModel& From
    ):
        DistributorModelIdValue(From.DistributorModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        InboxNamespaceIdValue(From.InboxNamespaceIdValue),
        WhiteListTargetIdsValue(From.WhiteListTargetIdsValue)
    {
    }

    TSharedPtr<FDistributorModel> FDistributorModel::WithDistributorModelId(
        const TOptional<FString> DistributorModelId
    )
    {
        this->DistributorModelIdValue = DistributorModelId;
        return SharedThis(this);
    }

    TSharedPtr<FDistributorModel> FDistributorModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FDistributorModel> FDistributorModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FDistributorModel> FDistributorModel::WithInboxNamespaceId(
        const TOptional<FString> InboxNamespaceId
    )
    {
        this->InboxNamespaceIdValue = InboxNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FDistributorModel> FDistributorModel::WithWhiteListTargetIds(
        const TSharedPtr<TArray<FString>> WhiteListTargetIds
    )
    {
        this->WhiteListTargetIdsValue = WhiteListTargetIds;
        return SharedThis(this);
    }
    TOptional<FString> FDistributorModel::GetDistributorModelId() const
    {
        return DistributorModelIdValue;
    }
    TOptional<FString> FDistributorModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FDistributorModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FDistributorModel::GetInboxNamespaceId() const
    {
        return InboxNamespaceIdValue;
    }
    TSharedPtr<TArray<FString>> FDistributorModel::GetWhiteListTargetIds() const
    {
        return WhiteListTargetIdsValue;
    }

    TOptional<FString> FDistributorModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):model:(?<distributorName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDistributorModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):model:(?<distributorName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDistributorModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):model:(?<distributorName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDistributorModel::GetDistributorNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):distributor:(?<namespaceName>.+):model:(?<distributorName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FDistributorModel> FDistributorModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDistributorModel>()
            ->WithDistributorModelId(Data->HasField("distributorModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("distributorModelId", v))
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithInboxNamespaceId(Data->HasField("inboxNamespaceId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("inboxNamespaceId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithWhiteListTargetIds(Data->HasField("whiteListTargetIds") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("whiteListTargetIds") && Data->HasTypedField<EJson::Array>("whiteListTargetIds"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("whiteListTargetIds"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FDistributorModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DistributorModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("distributorModelId", DistributorModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (InboxNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("inboxNamespaceId", InboxNamespaceIdValue.GetValue());
        }
        if (WhiteListTargetIdsValue != nullptr && WhiteListTargetIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *WhiteListTargetIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("whiteListTargetIds", v);
        }
        return JsonRootObject;
    }

    FString FDistributorModel::TypeName = "DistributorModel";
}