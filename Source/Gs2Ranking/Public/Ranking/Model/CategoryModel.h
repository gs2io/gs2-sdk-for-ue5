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
#include "Core/Gs2Object.h"
#include "GlobalRankingSetting.h"
#include "Scope.h"

namespace Gs2::Ranking::Model
{
    class GS2RANKING_API FCategoryModel final : public Gs2Object, public TSharedFromThis<FCategoryModel>
    {
        TOptional<FString> CategoryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<bool> SumValue;
        TOptional<FString> OrderDirectionValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<FGlobalRankingSetting> GlobalRankingSettingValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;
        TOptional<bool> UniqueByUserIdValue;
        TOptional<int32> CalculateFixedTimingHourValue;
        TOptional<int32> CalculateFixedTimingMinuteValue;
        TOptional<int32> CalculateIntervalMinutesValue;
        TSharedPtr<TArray<TSharedPtr<FScope>>> AdditionalScopesValue;
        TSharedPtr<TArray<FString>> IgnoreUserIdsValue;
        TOptional<FString> GenerationValue;

    public:
        FCategoryModel();
        FCategoryModel(
            const FCategoryModel& From
        );
        virtual ~FCategoryModel() override = default;

        TSharedPtr<FCategoryModel> WithCategoryModelId(const TOptional<FString> CategoryModelId);
        TSharedPtr<FCategoryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FCategoryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCategoryModel> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FCategoryModel> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FCategoryModel> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FCategoryModel> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FCategoryModel> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FCategoryModel> WithGlobalRankingSetting(const TSharedPtr<FGlobalRankingSetting> GlobalRankingSetting);
        TSharedPtr<FCategoryModel> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FCategoryModel> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);
        TSharedPtr<FCategoryModel> WithUniqueByUserId(const TOptional<bool> UniqueByUserId);
        TSharedPtr<FCategoryModel> WithCalculateFixedTimingHour(const TOptional<int32> CalculateFixedTimingHour);
        TSharedPtr<FCategoryModel> WithCalculateFixedTimingMinute(const TOptional<int32> CalculateFixedTimingMinute);
        TSharedPtr<FCategoryModel> WithCalculateIntervalMinutes(const TOptional<int32> CalculateIntervalMinutes);
        TSharedPtr<FCategoryModel> WithAdditionalScopes(const TSharedPtr<TArray<TSharedPtr<FScope>>> AdditionalScopes);
        TSharedPtr<FCategoryModel> WithIgnoreUserIds(const TSharedPtr<TArray<FString>> IgnoreUserIds);
        TSharedPtr<FCategoryModel> WithGeneration(const TOptional<FString> Generation);

        TOptional<FString> GetCategoryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetMinimumValue() const;
        FString GetMinimumValueString() const;
        TOptional<int64> GetMaximumValue() const;
        FString GetMaximumValueString() const;
        TOptional<bool> GetSum() const;
        FString GetSumString() const;
        TOptional<FString> GetOrderDirection() const;
        TOptional<FString> GetScope() const;
        TSharedPtr<FGlobalRankingSetting> GetGlobalRankingSetting() const;
        TOptional<FString> GetEntryPeriodEventId() const;
        TOptional<FString> GetAccessPeriodEventId() const;
        TOptional<bool> GetUniqueByUserId() const;
        FString GetUniqueByUserIdString() const;
        TOptional<int32> GetCalculateFixedTimingHour() const;
        FString GetCalculateFixedTimingHourString() const;
        TOptional<int32> GetCalculateFixedTimingMinute() const;
        FString GetCalculateFixedTimingMinuteString() const;
        TOptional<int32> GetCalculateIntervalMinutes() const;
        FString GetCalculateIntervalMinutesString() const;
        TSharedPtr<TArray<TSharedPtr<FScope>>> GetAdditionalScopes() const;
        TSharedPtr<TArray<FString>> GetIgnoreUserIds() const;
        TOptional<FString> GetGeneration() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCategoryNameFromGrn(const FString Grn);

        static TSharedPtr<FCategoryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCategoryModel, ESPMode::ThreadSafe> FCategoryModelPtr;
}