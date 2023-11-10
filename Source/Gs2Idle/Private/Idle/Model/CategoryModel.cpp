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

#include "Idle/Model/CategoryModel.h"

namespace Gs2::Idle::Model
{
    FCategoryModel::FCategoryModel():
        CategoryModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        RewardIntervalMinutesValue(TOptional<int32>()),
        DefaultMaximumIdleMinutesValue(TOptional<int32>()),
        AcquireActionsValue(nullptr),
        IdlePeriodScheduleIdValue(TOptional<FString>()),
        ReceivePeriodScheduleIdValue(TOptional<FString>())
    {
    }

    FCategoryModel::FCategoryModel(
        const FCategoryModel& From
    ):
        CategoryModelIdValue(From.CategoryModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        RewardIntervalMinutesValue(From.RewardIntervalMinutesValue),
        DefaultMaximumIdleMinutesValue(From.DefaultMaximumIdleMinutesValue),
        AcquireActionsValue(From.AcquireActionsValue),
        IdlePeriodScheduleIdValue(From.IdlePeriodScheduleIdValue),
        ReceivePeriodScheduleIdValue(From.ReceivePeriodScheduleIdValue)
    {
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithCategoryModelId(
        const TOptional<FString> CategoryModelId
    )
    {
        this->CategoryModelIdValue = CategoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithRewardIntervalMinutes(
        const TOptional<int32> RewardIntervalMinutes
    )
    {
        this->RewardIntervalMinutesValue = RewardIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithDefaultMaximumIdleMinutes(
        const TOptional<int32> DefaultMaximumIdleMinutes
    )
    {
        this->DefaultMaximumIdleMinutesValue = DefaultMaximumIdleMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithIdlePeriodScheduleId(
        const TOptional<FString> IdlePeriodScheduleId
    )
    {
        this->IdlePeriodScheduleIdValue = IdlePeriodScheduleId;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithReceivePeriodScheduleId(
        const TOptional<FString> ReceivePeriodScheduleId
    )
    {
        this->ReceivePeriodScheduleIdValue = ReceivePeriodScheduleId;
        return SharedThis(this);
    }
    TOptional<FString> FCategoryModel::GetCategoryModelId() const
    {
        return CategoryModelIdValue;
    }
    TOptional<FString> FCategoryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FCategoryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FCategoryModel::GetRewardIntervalMinutes() const
    {
        return RewardIntervalMinutesValue;
    }

    FString FCategoryModel::GetRewardIntervalMinutesString() const
    {
        if (!RewardIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RewardIntervalMinutesValue.GetValue());
    }
    TOptional<int32> FCategoryModel::GetDefaultMaximumIdleMinutes() const
    {
        return DefaultMaximumIdleMinutesValue;
    }

    FString FCategoryModel::GetDefaultMaximumIdleMinutesString() const
    {
        if (!DefaultMaximumIdleMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DefaultMaximumIdleMinutesValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> FCategoryModel::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }
    TOptional<FString> FCategoryModel::GetIdlePeriodScheduleId() const
    {
        return IdlePeriodScheduleIdValue;
    }
    TOptional<FString> FCategoryModel::GetReceivePeriodScheduleId() const
    {
        return ReceivePeriodScheduleIdValue;
    }

    TOptional<FString> FCategoryModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):model:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):model:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):model:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModel::GetCategoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):model:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FCategoryModel> FCategoryModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCategoryModel>()
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
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCategoryModel::ToJson() const
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
        return JsonRootObject;
    }

    FString FCategoryModel::TypeName = "CategoryModel";
}