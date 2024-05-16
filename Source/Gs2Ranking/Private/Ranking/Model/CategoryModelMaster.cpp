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
        OrderDirectionValue(TOptional<FString>()),
        ScopeValue(TOptional<FString>()),
        UniqueByUserIdValue(TOptional<bool>()),
        SumValue(TOptional<bool>()),
        CalculateFixedTimingHourValue(TOptional<int32>()),
        CalculateFixedTimingMinuteValue(TOptional<int32>()),
        CalculateIntervalMinutesValue(TOptional<int32>()),
        AdditionalScopesValue(nullptr),
        EntryPeriodEventIdValue(TOptional<FString>()),
        AccessPeriodEventIdValue(TOptional<FString>()),
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
        OrderDirectionValue(From.OrderDirectionValue),
        ScopeValue(From.ScopeValue),
        UniqueByUserIdValue(From.UniqueByUserIdValue),
        SumValue(From.SumValue),
        CalculateFixedTimingHourValue(From.CalculateFixedTimingHourValue),
        CalculateFixedTimingMinuteValue(From.CalculateFixedTimingMinuteValue),
        CalculateIntervalMinutesValue(From.CalculateIntervalMinutesValue),
        AdditionalScopesValue(From.AdditionalScopesValue),
        EntryPeriodEventIdValue(From.EntryPeriodEventIdValue),
        AccessPeriodEventIdValue(From.AccessPeriodEventIdValue),
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

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithUniqueByUserId(
        const TOptional<bool> UniqueByUserId
    )
    {
        this->UniqueByUserIdValue = UniqueByUserId;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModelMaster> FCategoryModelMaster::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
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
    TOptional<FString> FCategoryModelMaster::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }
    TOptional<FString> FCategoryModelMaster::GetScope() const
    {
        return ScopeValue;
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
    TOptional<FString> FCategoryModelMaster::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }
    TOptional<FString> FCategoryModelMaster::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
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
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
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
            ->WithOrderDirection(Data->HasField(ANSI_TO_TCHAR("orderDirection")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("orderDirection"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithScope(Data->HasField(ANSI_TO_TCHAR("scope")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scope"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
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
            ->WithSum(Data->HasField(ANSI_TO_TCHAR("sum")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("sum"), v))
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
                    auto v = MakeShared<TArray<Model::FScopePtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("additionalScopes")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("additionalScopes")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("additionalScopes")))
                        {
                            v->Add(Model::FScope::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FScopePtr>>())
            ->WithEntryPeriodEventId(Data->HasField(ANSI_TO_TCHAR("entryPeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("entryPeriodEventId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAccessPeriodEventId(Data->HasField(ANSI_TO_TCHAR("accessPeriodEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("accessPeriodEventId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithIgnoreUserIds(Data->HasField(ANSI_TO_TCHAR("ignoreUserIds")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("ignoreUserIds")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("ignoreUserIds")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("ignoreUserIds")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithGeneration(Data->HasField(ANSI_TO_TCHAR("generation")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("generation"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
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
        if (MinimumValueValue.IsSet())
        {
            JsonRootObject->SetStringField("minimumValue", FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue()));
        }
        if (MaximumValueValue.IsSet())
        {
            JsonRootObject->SetStringField("maximumValue", FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue()));
        }
        if (OrderDirectionValue.IsSet())
        {
            JsonRootObject->SetStringField("orderDirection", OrderDirectionValue.GetValue());
        }
        if (ScopeValue.IsSet())
        {
            JsonRootObject->SetStringField("scope", ScopeValue.GetValue());
        }
        if (UniqueByUserIdValue.IsSet())
        {
            JsonRootObject->SetBoolField("uniqueByUserId", UniqueByUserIdValue.GetValue());
        }
        if (SumValue.IsSet())
        {
            JsonRootObject->SetBoolField("sum", SumValue.GetValue());
        }
        if (CalculateFixedTimingHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("calculateFixedTimingHour", CalculateFixedTimingHourValue.GetValue());
        }
        if (CalculateFixedTimingMinuteValue.IsSet())
        {
            JsonRootObject->SetNumberField("calculateFixedTimingMinute", CalculateFixedTimingMinuteValue.GetValue());
        }
        if (CalculateIntervalMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("calculateIntervalMinutes", CalculateIntervalMinutesValue.GetValue());
        }
        if (AdditionalScopesValue != nullptr && AdditionalScopesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AdditionalScopesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("additionalScopes", v);
        }
        if (EntryPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("entryPeriodEventId", EntryPeriodEventIdValue.GetValue());
        }
        if (AccessPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("accessPeriodEventId", AccessPeriodEventIdValue.GetValue());
        }
        if (IgnoreUserIdsValue != nullptr && IgnoreUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *IgnoreUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("ignoreUserIds", v);
        }
        if (GenerationValue.IsSet())
        {
            JsonRootObject->SetStringField("generation", GenerationValue.GetValue());
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