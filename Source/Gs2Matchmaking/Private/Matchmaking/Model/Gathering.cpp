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

#include "Matchmaking/Model/Gathering.h"

namespace Gs2::Matchmaking::Model
{
    FGathering::FGathering():
        GatheringIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        AttributeRangesValue(nullptr),
        CapacityOfRolesValue(nullptr),
        AllowUserIdsValue(nullptr),
        MetadataValue(TOptional<FString>()),
        ExpiresAtValue(TOptional<int64>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FGathering::FGathering(
        const FGathering& From
    ):
        GatheringIdValue(From.GatheringIdValue),
        NameValue(From.NameValue),
        AttributeRangesValue(From.AttributeRangesValue),
        CapacityOfRolesValue(From.CapacityOfRolesValue),
        AllowUserIdsValue(From.AllowUserIdsValue),
        MetadataValue(From.MetadataValue),
        ExpiresAtValue(From.ExpiresAtValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FGathering> FGathering::WithGatheringId(
        const TOptional<FString> GatheringId
    )
    {
        this->GatheringIdValue = GatheringId;
        return SharedThis(this);
    }

    TSharedPtr<FGathering> FGathering::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FGathering> FGathering::WithAttributeRanges(
        const TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRanges
    )
    {
        this->AttributeRangesValue = AttributeRanges;
        return SharedThis(this);
    }

    TSharedPtr<FGathering> FGathering::WithCapacityOfRoles(
        const TSharedPtr<TArray<TSharedPtr<Model::FCapacityOfRole>>> CapacityOfRoles
    )
    {
        this->CapacityOfRolesValue = CapacityOfRoles;
        return SharedThis(this);
    }

    TSharedPtr<FGathering> FGathering::WithAllowUserIds(
        const TSharedPtr<TArray<FString>> AllowUserIds
    )
    {
        this->AllowUserIdsValue = AllowUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FGathering> FGathering::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FGathering> FGathering::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TSharedPtr<FGathering> FGathering::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGathering> FGathering::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGathering> FGathering::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FGathering::GetGatheringId() const
    {
        return GatheringIdValue;
    }
    TOptional<FString> FGathering::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> FGathering::GetAttributeRanges() const
    {
        return AttributeRangesValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FCapacityOfRole>>> FGathering::GetCapacityOfRoles() const
    {
        return CapacityOfRolesValue;
    }
    TSharedPtr<TArray<FString>> FGathering::GetAllowUserIds() const
    {
        return AllowUserIdsValue;
    }
    TOptional<FString> FGathering::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FGathering::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FGathering::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }
    TOptional<int64> FGathering::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FGathering::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FGathering::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FGathering::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FGathering::GetRevision() const
    {
        return RevisionValue;
    }

    FString FGathering::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FGathering::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):gathering:(?<gatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGathering::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):gathering:(?<gatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGathering::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):gathering:(?<gatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGathering::GetGatheringNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):gathering:(?<gatheringName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FGathering> FGathering::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGathering>()
            ->WithGatheringId(Data->HasField("gatheringId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("gatheringId", v))
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
            ->WithAttributeRanges(Data->HasField("attributeRanges") ? [Data]() -> TSharedPtr<TArray<Model::FAttributeRangePtr>>
                {
                    auto v = MakeShared<TArray<Model::FAttributeRangePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("attributeRanges") && Data->HasTypedField<EJson::Array>("attributeRanges"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("attributeRanges"))
                        {
                            v->Add(Model::FAttributeRange::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAttributeRangePtr>>())
            ->WithCapacityOfRoles(Data->HasField("capacityOfRoles") ? [Data]() -> TSharedPtr<TArray<Model::FCapacityOfRolePtr>>
                {
                    auto v = MakeShared<TArray<Model::FCapacityOfRolePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("capacityOfRoles") && Data->HasTypedField<EJson::Array>("capacityOfRoles"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("capacityOfRoles"))
                        {
                            v->Add(Model::FCapacityOfRole::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FCapacityOfRolePtr>>())
            ->WithAllowUserIds(Data->HasField("allowUserIds") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("allowUserIds") && Data->HasTypedField<EJson::Array>("allowUserIds"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("allowUserIds"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExpiresAt(Data->HasField("expiresAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("expiresAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
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
                }() : TOptional<int64>())
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

    TSharedPtr<FJsonObject> FGathering::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GatheringIdValue.IsSet())
        {
            JsonRootObject->SetStringField("gatheringId", GatheringIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (AttributeRangesValue != nullptr && AttributeRangesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AttributeRangesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("attributeRanges", v);
        }
        if (CapacityOfRolesValue != nullptr && CapacityOfRolesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *CapacityOfRolesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("capacityOfRoles", v);
        }
        if (AllowUserIdsValue != nullptr && AllowUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AllowUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("allowUserIds", v);
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ExpiresAtValue.IsSet())
        {
            JsonRootObject->SetStringField("expiresAt", FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue()));
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FGathering::TypeName = "Gathering";
}