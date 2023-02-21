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

namespace Gs2::Ranking::Request
{
    class FUpdateCategoryModelMasterRequest;

    class GS2RANKING_API FUpdateCategoryModelMasterRequest final : public TSharedFromThis<FUpdateCategoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<FString> OrderDirectionValue;
        TOptional<FString> ScopeValue;
        TOptional<bool> UniqueByUserIdValue;
        TOptional<int32> CalculateFixedTimingHourValue;
        TOptional<int32> CalculateFixedTimingMinuteValue;
        TOptional<int32> CalculateIntervalMinutesValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;
        TOptional<FString> GenerationValue;
        
    public:
        
        FUpdateCategoryModelMasterRequest();
        FUpdateCategoryModelMasterRequest(
            const FUpdateCategoryModelMasterRequest& From
        );
        ~FUpdateCategoryModelMasterRequest() = default;

        TSharedPtr<FUpdateCategoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithUniqueByUserId(const TOptional<bool> UniqueByUserId);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithCalculateFixedTimingHour(const TOptional<int32> CalculateFixedTimingHour);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithCalculateFixedTimingMinute(const TOptional<int32> CalculateFixedTimingMinute);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithCalculateIntervalMinutes(const TOptional<int32> CalculateIntervalMinutes);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithGeneration(const TOptional<FString> Generation);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
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
        TOptional<int32> GetCalculateFixedTimingHour() const;
        FString GetCalculateFixedTimingHourString() const;
        TOptional<int32> GetCalculateFixedTimingMinute() const;
        FString GetCalculateFixedTimingMinuteString() const;
        TOptional<int32> GetCalculateIntervalMinutes() const;
        FString GetCalculateIntervalMinutesString() const;
        TOptional<FString> GetEntryPeriodEventId() const;
        TOptional<FString> GetAccessPeriodEventId() const;
        TOptional<FString> GetGeneration() const;

        static TSharedPtr<FUpdateCategoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCategoryModelMasterRequest, ESPMode::ThreadSafe> FUpdateCategoryModelMasterRequestPtr;
}