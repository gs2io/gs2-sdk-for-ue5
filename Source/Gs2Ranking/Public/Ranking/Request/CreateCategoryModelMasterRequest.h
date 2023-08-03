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
#include "../Model/Scope.h"

namespace Gs2::Ranking::Request
{
    class FCreateCategoryModelMasterRequest;

    class GS2RANKING_API FCreateCategoryModelMasterRequest final : public TSharedFromThis<FCreateCategoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
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
        TSharedPtr<TArray<TSharedPtr<Model::FScope>>> AdditionalScopesValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;
        TSharedPtr<TArray<FString>> IgnoreUserIdsValue;
        TOptional<FString> GenerationValue;
        
    public:
        
        FCreateCategoryModelMasterRequest();
        FCreateCategoryModelMasterRequest(
            const FCreateCategoryModelMasterRequest& From
        );
        ~FCreateCategoryModelMasterRequest() = default;

        TSharedPtr<FCreateCategoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithUniqueByUserId(const TOptional<bool> UniqueByUserId);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithCalculateFixedTimingHour(const TOptional<int32> CalculateFixedTimingHour);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithCalculateFixedTimingMinute(const TOptional<int32> CalculateFixedTimingMinute);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithCalculateIntervalMinutes(const TOptional<int32> CalculateIntervalMinutes);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithAdditionalScopes(const TSharedPtr<TArray<TSharedPtr<Model::FScope>>> AdditionalScopes);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithIgnoreUserIds(
            const TSharedPtr<TArray<FString>> IgnoreUserIds);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithGeneration(const TOptional<FString> Generation);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
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
        FString GetCalculateIntervalMinutesString() const;TSharedPtr<TArray<TSharedPtr<Model::FScope>>> GetAdditionalScopes() const;
        TOptional<FString> GetEntryPeriodEventId() const;
        TOptional<FString> GetAccessPeriodEventId() const;
        TSharedPtr<TArray<FString>> GetIgnoreUserIds() const;
        TOptional<FString> GetGeneration() const;

        static TSharedPtr<FCreateCategoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateCategoryModelMasterRequest, ESPMode::ThreadSafe> FCreateCategoryModelMasterRequestPtr;
}