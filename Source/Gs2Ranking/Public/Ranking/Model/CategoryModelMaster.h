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

#pragma once

#include "CoreMinimal.h"

namespace Gs2::Ranking::Model
{
    class GS2RANKING_API FCategoryModelMaster final : public TSharedFromThis<FCategoryModelMaster>
    {
        TOptional<FString> CategoryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<FString> OrderDirectionValue;
        TOptional<FString> ScopeValue;
        TOptional<bool> UniqueByUserIdValue;
        TOptional<bool> SumValue;
        TOptional<int32> CalculateFixedTimingHourValue;
        TOptional<int32> CalculateFixedTimingMinuteValue;
        TOptional<int32> CalculateIntervalMinutesValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;
        TSharedPtr<TArray<FString>> IgnoreUserIdsValue;
        TOptional<FString> GenerationValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FCategoryModelMaster();
        FCategoryModelMaster(
            const FCategoryModelMaster& From
        );
        ~FCategoryModelMaster() = default;

        TSharedPtr<FCategoryModelMaster> WithCategoryModelId(const TOptional<FString> CategoryModelId);
        TSharedPtr<FCategoryModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FCategoryModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCategoryModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCategoryModelMaster> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FCategoryModelMaster> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FCategoryModelMaster> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FCategoryModelMaster> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FCategoryModelMaster> WithUniqueByUserId(const TOptional<bool> UniqueByUserId);
        TSharedPtr<FCategoryModelMaster> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FCategoryModelMaster> WithCalculateFixedTimingHour(const TOptional<int32> CalculateFixedTimingHour);
        TSharedPtr<FCategoryModelMaster> WithCalculateFixedTimingMinute(const TOptional<int32> CalculateFixedTimingMinute);
        TSharedPtr<FCategoryModelMaster> WithCalculateIntervalMinutes(const TOptional<int32> CalculateIntervalMinutes);
        TSharedPtr<FCategoryModelMaster> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FCategoryModelMaster> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);
        TSharedPtr<FCategoryModelMaster> WithIgnoreUserIds(const TSharedPtr<TArray<FString>> IgnoreUserIds);
        TSharedPtr<FCategoryModelMaster> WithGeneration(const TOptional<FString> Generation);
        TSharedPtr<FCategoryModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FCategoryModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetCategoryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetMinimumValue() const;
        FString GetMinimumValueString() const;
        TOptional<int64> GetMaximumValue() const;
        FString GetMaximumValueString() const;
        TOptional<FString> GetOrderDirection() const;
        TOptional<FString> GetScope() const;
        TOptional<bool> GetUniqueByUserId() const;
        FString GetUniqueByUserIdString() const;
        TOptional<bool> GetSum() const;
        FString GetSumString() const;
        TOptional<int32> GetCalculateFixedTimingHour() const;
        FString GetCalculateFixedTimingHourString() const;
        TOptional<int32> GetCalculateFixedTimingMinute() const;
        FString GetCalculateFixedTimingMinuteString() const;
        TOptional<int32> GetCalculateIntervalMinutes() const;
        FString GetCalculateIntervalMinutesString() const;
        TOptional<FString> GetEntryPeriodEventId() const;
        TOptional<FString> GetAccessPeriodEventId() const;
        TSharedPtr<TArray<FString>> GetIgnoreUserIds() const;
        TOptional<FString> GetGeneration() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCategoryNameFromGrn(const FString Grn);

        static TSharedPtr<FCategoryModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCategoryModelMaster, ESPMode::ThreadSafe> FCategoryModelMasterPtr;
}