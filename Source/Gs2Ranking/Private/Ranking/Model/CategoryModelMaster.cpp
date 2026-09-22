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

#include "Ranking/Model/CategoryModelMaster.h"

namespace Gs2::Ranking::Model
{
    FCategoryModelMaster::FCategoryModelMaster():
        CategoryModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MinimumValueValue(TOptional<int64>()),
        MaximumValueValue(TOptional<int64>()),
        SumValue(TOptional<bool>()),
        OrderDirectionValue(TOptional<FString>()),
        ScopeValue(TOptional<FString>()),
        GlobalRankingSettingValue(nullptr),
        EntryPeriodEventIdValue(TOptional<FString>()),
        AccessPeriodEventIdValue(TOptional<FString>()),
        UniqueByUserIdValue(TOptional<bool>()),
        CalculateFixedTimingHourValue(TOptional<int32>()),
        CalculateFixedTimingMinuteValue(TOptional<int32>()),
        CalculateIntervalMinutesValue(TOptional<int32>()),
        AdditionalScopesValue(nullptr),
        IgnoreUserIdsValue(nullptr),
        GenerationValue(TOptional<FString>()),
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
        MinimumValueValue(From.MinimumValueValue),
        MaximumValueValue(From.MaximumValueValue),
        SumValue(From.SumValue),
        OrderDirectionValue(From.OrderDirectionValue),
        ScopeValue(From.ScopeValue),
        GlobalRankingSettingValue(From.GlobalRankingSettingValue),
        EntryPeriodEventIdValue(From.EntryPeriodEventIdValue),
        AccessPeriodEventIdValue(From.AccessPeriodEventIdValue),
        UniqueByUserIdValue(From.UniqueByUserIdValue),
        CalculateFixedTimingHourValue(From.CalculateFixedTimingHourValue),
        CalculateFixedTimingMinuteValue(From.CalculateFixedTimingMinuteValue),
        CalculateIntervalMinutesValue(From.CalculateIntervalMinutesValue),
        AdditionalScopesValue(From.AdditionalScopesValue),
        IgnoreUserIdsValue(From.IgnoreUserIdsValue),
        GenerationValue(From.GenerationValue),
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

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithMinimumValue(
        const TOptional<int64> MinimumValue
    )
    {
        this->MinimumValueValue = MinimumValue;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithMaximumValue(
        const TOptional<int64> MaximumValue
    )
    {
        this->MaximumValueValue = MaximumValue;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithOrderDirection(
        const TOptional<FString> OrderDirection
    )
    {
        this->OrderDirectionValue = OrderDirection;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithScope(
        const TOptional<FString> Scope
    )
    {
        this->ScopeValue = Scope;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithGlobalRankingSetting(
        const TSharedPtr<FGlobalRankingSetting> GlobalRankingSetting
    )
    {
        this->GlobalRankingSettingValue = GlobalRankingSetting;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithUniqueByUserId(
        const TOptional<bool> UniqueByUserId
    )
    {
        this->UniqueByUserIdValue = UniqueByUserId;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithCalculateFixedTimingHour(
        const TOptional<int32> CalculateFixedTimingHour
    )
    {
        this->CalculateFixedTimingHourValue = CalculateFixedTimingHour;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithCalculateFixedTimingMinute(
        const TOptional<int32> CalculateFixedTimingMinute
    )
    {
        this->CalculateFixedTimingMinuteValue = CalculateFixedTimingMinute;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithCalculateIntervalMinutes(
        const TOptional<int32> CalculateIntervalMinutes
    )
    {
        this->CalculateIntervalMinutesValue = CalculateIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithAdditionalScopes(
        const TSharedPtr<TArray<TSharedPtr<Model::FScope>>> AdditionalScopes
    )
    {
        this->AdditionalScopesValue = AdditionalScopes;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithIgnoreUserIds(
        const TSharedPtr<TArray<FString>> IgnoreUserIds
    )
    {
        this->IgnoreUserIdsValue = IgnoreUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithGeneration(
        const TOptional<FString> Generation
    )
    {
        this->GenerationValue = Generation;
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
    TOptional<int64> FCategoryModelMaster::GetMinimumValue() const
    {
        return MinimumValueValue;
    }

    FString FCategoryModelMaster::GetMinimumValueString() const
    {
        if (!MinimumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue());
    }
    TOptional<int64> FCategoryModelMaster::GetMaximumValue() const
    {
        return MaximumValueValue;
    }

    FString FCategoryModelMaster::GetMaximumValueString() const
    {
        if (!MaximumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue());
    }
    TOptional<bool> FCategoryModelMaster::GetSum() const
    {
        return SumValue;
    }

    FString FCategoryModelMaster::GetSumString() const
    {
        if (!SumValue.IsSet())
        {
            return FString("null");
        }
        return FString(SumValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FCategoryModelMaster::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }
    TOptional<FString> FCategoryModelMaster::GetScope() const
    {
        return ScopeValue;
    }
    TSharedPtr<FGlobalRankingSetting> FCategoryModelMaster::GetGlobalRankingSetting() const
    {
        return GlobalRankingSettingValue;
    }
    TOptional<FString> FCategoryModelMaster::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }
    TOptional<FString> FCategoryModelMaster::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }
    TOptional<bool> FCategoryModelMaster::GetUniqueByUserId() const
    {
        return UniqueByUserIdValue;
    }

    FString FCategoryModelMaster::GetUniqueByUserIdString() const
    {
        if (!UniqueByUserIdValue.IsSet())
        {
            return FString("null");
        }
        return FString(UniqueByUserIdValue.GetValue() ? "true" : "false");
    }
    TOptional<int32> FCategoryModelMaster::GetCalculateFixedTimingHour() const
    {
        return CalculateFixedTimingHourValue;
    }

    FString FCategoryModelMaster::GetCalculateFixedTimingHourString() const
    {
        if (!CalculateFixedTimingHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CalculateFixedTimingHourValue.GetValue());
    }
    TOptional<int32> FCategoryModelMaster::GetCalculateFixedTimingMinute() const
    {
        return CalculateFixedTimingMinuteValue;
    }

    FString FCategoryModelMaster::GetCalculateFixedTimingMinuteString() const
    {
        if (!CalculateFixedTimingMinuteValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CalculateFixedTimingMinuteValue.GetValue());
    }
    TOptional<int32> FCategoryModelMaster::GetCalculateIntervalMinutes() const
    {
        return CalculateIntervalMinutesValue;
    }

    FString FCategoryModelMaster::GetCalculateIntervalMinutesString() const
    {
        if (!CalculateIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CalculateIntervalMinutesValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FScope>>> FCategoryModelMaster::GetAdditionalScopes() const
    {
        return AdditionalScopesValue;
    }
    TSharedPtr<TArray<FString>> FCategoryModelMaster::GetIgnoreUserIds() const
    {
        return IgnoreUserIdsValue;
    }
    TOptional<FString> FCategoryModelMaster::GetGeneration() const
    {
        return GenerationValue;
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
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking:(?<namespaceName>.+):categoryModelMaster:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking:(?<namespaceName>.+):categoryModelMaster:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking:(?<namespaceName>.+):categoryModelMaster:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModelMaster::GetCategoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking:(?<namespaceName>.+):categoryModelMaster:(?<categoryName>.+)"));
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
            ->WithCategoryModelId(Data->HasField(ANSI_TO_TCHAR("categoryModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("categoryModelId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMinimumValue(Data->HasField(ANSI_TO_TCHAR("minimumValue")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("minimumValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithMaximumValue(Data->HasField(ANSI_TO_TCHAR("maximumValue")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maximumValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithSum(Data->HasField(ANSI_TO_TCHAR("sum")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("sum"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithOrderDirection(Data->HasField(ANSI_TO_TCHAR("orderDirection")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("orderDirection"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithScope(Data->HasField(ANSI_TO_TCHAR("scope")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scope"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGlobalRankingSetting(Data->HasField(ANSI_TO_TCHAR("globalRankingSetting")) ? [Data]() -> Model::FGlobalRankingSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("globalRankingSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FGlobalRankingSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("globalRankingSetting")));
                 }() : nullptr)
            ->WithEntryPeriodEventId(Data->HasField(ANSI_TO_TCHAR("entryPeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("entryPeriodEventId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAccessPeriodEventId(Data->HasField(ANSI_TO_TCHAR("accessPeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("accessPeriodEventId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUniqueByUserId(Data->HasField(ANSI_TO_TCHAR("uniqueByUserId")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("uniqueByUserId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithCalculateFixedTimingHour(Data->HasField(ANSI_TO_TCHAR("calculateFixedTimingHour")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("calculateFixedTimingHour"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCalculateFixedTimingMinute(Data->HasField(ANSI_TO_TCHAR("calculateFixedTimingMinute")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("calculateFixedTimingMinute"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCalculateIntervalMinutes(Data->HasField(ANSI_TO_TCHAR("calculateIntervalMinutes")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("calculateIntervalMinutes"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAdditionalScopes(Data->HasField(ANSI_TO_TCHAR("additionalScopes")) ? [Data]() -> TSharedPtr<TArray<Model::FScopePtr>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("additionalScopes")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<Model::FScopePtr>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("additionalScopes")))
                    {
                        v->Add(Model::FScope::FromJson(JsonObjectValue->AsObject()));
                    }
                    return v;
                 }() : nullptr)
            ->WithIgnoreUserIds(Data->HasField(ANSI_TO_TCHAR("ignoreUserIds")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("ignoreUserIds")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<FString>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("ignoreUserIds")))
                    {
                        v->Add(JsonObjectValue->AsString());
                    }
                    return v;
                 }() : nullptr)
            ->WithGeneration(Data->HasField(ANSI_TO_TCHAR("generation")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("generation"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
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
            JsonRootObject->SetStringField(TEXT("categoryModelId"), CategoryModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("description"), DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("metadata"), MetadataValue.GetValue());
        }
        if (MinimumValueValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("minimumValue"), FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue()));
        }
        if (MaximumValueValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("maximumValue"), FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue()));
        }
        if (SumValue.IsSet())
        {
            JsonRootObject->SetBoolField(TEXT("sum"), SumValue.GetValue());
        }
        if (OrderDirectionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("orderDirection"), OrderDirectionValue.GetValue());
        }
        if (ScopeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("scope"), ScopeValue.GetValue());
        }
        if (GlobalRankingSettingValue != nullptr && GlobalRankingSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("globalRankingSetting"), GlobalRankingSettingValue->ToJson());
        }
        if (EntryPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("entryPeriodEventId"), EntryPeriodEventIdValue.GetValue());
        }
        if (AccessPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("accessPeriodEventId"), AccessPeriodEventIdValue.GetValue());
        }
        if (UniqueByUserIdValue.IsSet())
        {
            JsonRootObject->SetBoolField(TEXT("uniqueByUserId"), UniqueByUserIdValue.GetValue());
        }
        if (CalculateFixedTimingHourValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("calculateFixedTimingHour"), CalculateFixedTimingHourValue.GetValue());
        }
        if (CalculateFixedTimingMinuteValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("calculateFixedTimingMinute"), CalculateFixedTimingMinuteValue.GetValue());
        }
        if (CalculateIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("calculateIntervalMinutes"), CalculateIntervalMinutesValue.GetValue());
        }
        if (AdditionalScopesValue != nullptr && AdditionalScopesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AdditionalScopesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("additionalScopes"), v);
        }
        if (IgnoreUserIdsValue != nullptr && IgnoreUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *IgnoreUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField(TEXT("ignoreUserIds"), v);
        }
        if (GenerationValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("generation"), GenerationValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("createdAt"), FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("updatedAt"), FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("revision"), FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FCategoryModelMaster::TypeName = "CategoryModelMaster";
}
#include "Ranking/Model/Cache/CategoryModelMaster.h"

namespace Gs2::Ranking::Model::Cache
{
    FString FCategoryModelMasterCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("ranking:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":CategoryModelMaster");
    }

    FString FCategoryModelMasterCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentCategoryName
    )
    {
        return
            FString()
            + CacheOwnerArgumentCategoryName.Get(FString())
            ;
    }

    bool FCategoryModelMasterCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentCategoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Ranking::Model::FCategoryModelMasterPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Ranking::Model::FCategoryModelMasterPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Ranking::Model::FCategoryModelMaster>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentCategoryName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FCategoryModelMasterCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentCategoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Ranking::Model::FCategoryModelMasterPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentCategoryName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Ranking::Model::FCategoryModelMasterPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Ranking::Model::FCategoryModelMaster>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Ranking::Model::FCategoryModelMaster::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FCategoryModelMasterCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Ranking::Model::FCategoryModelMasterPtr& Item
    )
    {
        if (!Item.IsValid()) return FString();
        Put(
            Cache,
            NamespaceName,
            Item->GetName(),
            TimeOffset,
            Item
        );
        return CreateCacheParentKey(
            NamespaceName,
            TimeOffset
        );
    }

    void FCategoryModelMasterCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentCategoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Ranking::Model::FCategoryModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentCategoryName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelMasterCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentCategoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Ranking::Model::FCategoryModelMasterPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Ranking::Model::FCategoryModelMasterPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        const auto FetchImplSnapshot = CacheOwnerArgumentFetchImpl;
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        if (!FetchImplSnapshot)
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("fetchImpl"), TEXT("fetchImpl is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Gs2::Ranking::Model::FCategoryModelMasterPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentCategoryName,
                CacheOwnerArgumentTimeOffset,
                CacheOwnerFetchedItem
            );
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFetchedItem;
            return nullptr;
        }
        if (!CacheOwnerError->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return CacheOwnerError;
        }
        Put(
            CacheSnapshot,
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentCategoryName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("categoryModelMaster"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FCategoryModelMasterCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Ranking::Model::FCategoryModelMasterPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Ranking::Model::FCategoryModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Ranking::Model::FCategoryModelMasterPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Ranking::Model::FCategoryModelMaster>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FCategoryModelMasterCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Ranking::Model::FCategoryModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}