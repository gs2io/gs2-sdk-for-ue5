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

#include "Idle/Model/CategoryModelMaster.h"

namespace Gs2::Idle::Model
{
    FCategoryModelMaster::FCategoryModelMaster():
        CategoryModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        RewardIntervalMinutesValue(TOptional<int32>()),
        DefaultMaximumIdleMinutesValue(TOptional<int32>()),
        AcquireActionsValue(nullptr),
        IdlePeriodScheduleIdValue(TOptional<FString>()),
        ReceivePeriodScheduleIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FCategoryModelMaster::FCategoryModelMaster(
        const FCategoryModelMaster& From
    ):
        CategoryModelIdValue(From.CategoryModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        RewardIntervalMinutesValue(From.RewardIntervalMinutesValue),
        DefaultMaximumIdleMinutesValue(From.DefaultMaximumIdleMinutesValue),
        AcquireActionsValue(From.AcquireActionsValue),
        IdlePeriodScheduleIdValue(From.IdlePeriodScheduleIdValue),
        ReceivePeriodScheduleIdValue(From.ReceivePeriodScheduleIdValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithCategoryModelId(
        const TOptional<FString> CategoryModelId
    )
    {
        this->CategoryModelIdValue = CategoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithRewardIntervalMinutes(
        const TOptional<int32> RewardIntervalMinutes
    )
    {
        this->RewardIntervalMinutesValue = RewardIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithDefaultMaximumIdleMinutes(
        const TOptional<int32> DefaultMaximumIdleMinutes
    )
    {
        this->DefaultMaximumIdleMinutesValue = DefaultMaximumIdleMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithIdlePeriodScheduleId(
        const TOptional<FString> IdlePeriodScheduleId
    )
    {
        this->IdlePeriodScheduleIdValue = IdlePeriodScheduleId;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithReceivePeriodScheduleId(
        const TOptional<FString> ReceivePeriodScheduleId
    )
    {
        this->ReceivePeriodScheduleIdValue = ReceivePeriodScheduleId;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FCategoryModelMaster::GetCategoryModelId() const
    {
        return CategoryModelIdValue;
    }
    TOptional<FString> FCategoryModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FCategoryModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FCategoryModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FCategoryModelMaster::GetRewardIntervalMinutes() const
    {
        return RewardIntervalMinutesValue;
    }

    FString FCategoryModelMaster::GetRewardIntervalMinutesString() const
    {
        if (!RewardIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RewardIntervalMinutesValue.GetValue());
    }
    TOptional<int32> FCategoryModelMaster::GetDefaultMaximumIdleMinutes() const
    {
        return DefaultMaximumIdleMinutesValue;
    }

    FString FCategoryModelMaster::GetDefaultMaximumIdleMinutesString() const
    {
        if (!DefaultMaximumIdleMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DefaultMaximumIdleMinutesValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> FCategoryModelMaster::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }
    TOptional<FString> FCategoryModelMaster::GetIdlePeriodScheduleId() const
    {
        return IdlePeriodScheduleIdValue;
    }
    TOptional<FString> FCategoryModelMaster::GetReceivePeriodScheduleId() const
    {
        return ReceivePeriodScheduleIdValue;
    }
    TOptional<int64> FCategoryModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FCategoryModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FCategoryModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FCategoryModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FCategoryModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FCategoryModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FCategoryModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):model:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):model:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):model:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModelMaster::GetCategoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):model:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCategoryModelMaster>()
            ->WithCategoryModelId(Data->HasField("categoryModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("categoryModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRewardIntervalMinutes(Data->HasField("rewardIntervalMinutes") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("rewardIntervalMinutes", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithDefaultMaximumIdleMinutes(Data->HasField("defaultMaximumIdleMinutes") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("defaultMaximumIdleMinutes", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAcquireActions(Data->HasField("acquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionListPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionListPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("acquireActions") && Data->HasTypedField<EJson::Array>("acquireActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("acquireActions"))
                        {
                            v->Add(Model::FAcquireActionList::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionListPtr>>())
            ->WithIdlePeriodScheduleId(Data->HasField("idlePeriodScheduleId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("idlePeriodScheduleId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithReceivePeriodScheduleId(Data->HasField("receivePeriodScheduleId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("receivePeriodScheduleId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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

    TSharedPtr<FJsonObject> FCategoryModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CategoryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("categoryModelId", CategoryModelIdValue.GetValue());
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
        if (RewardIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("rewardIntervalMinutes", RewardIntervalMinutesValue.GetValue());
        }
        if (DefaultMaximumIdleMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("defaultMaximumIdleMinutes", DefaultMaximumIdleMinutesValue.GetValue());
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
        if (IdlePeriodScheduleIdValue.IsSet())
        {
            JsonRootObject->SetStringField("idlePeriodScheduleId", IdlePeriodScheduleIdValue.GetValue());
        }
        if (ReceivePeriodScheduleIdValue.IsSet())
        {
            JsonRootObject->SetStringField("receivePeriodScheduleId", ReceivePeriodScheduleIdValue.GetValue());
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

    FString FCategoryModelMaster::TypeName = "CategoryModelMaster";
}