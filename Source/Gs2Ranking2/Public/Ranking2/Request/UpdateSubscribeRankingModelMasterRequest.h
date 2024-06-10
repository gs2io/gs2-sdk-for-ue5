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

namespace Gs2::Ranking2::Request
{
    class FUpdateSubscribeRankingModelMasterRequest;

    class GS2RANKING2_API FUpdateSubscribeRankingModelMasterRequest final : public TSharedFromThis<FUpdateSubscribeRankingModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<bool> SumValue;
        TOptional<int32> ScoreTtlDaysValue;
        TOptional<FString> OrderDirectionValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;
        
    public:
        
        FUpdateSubscribeRankingModelMasterRequest();
        FUpdateSubscribeRankingModelMasterRequest(
            const FUpdateSubscribeRankingModelMasterRequest& From
        );
        ~FUpdateSubscribeRankingModelMasterRequest() = default;

        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithScoreTtlDays(const TOptional<int32> ScoreTtlDays);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetMinimumValue() const;
        FString GetMinimumValueString() const;
        TOptional<int64> GetMaximumValue() const;
        FString GetMaximumValueString() const;
        TOptional<bool> GetSum() const;
        FString GetSumString() const;
        TOptional<int32> GetScoreTtlDays() const;
        FString GetScoreTtlDaysString() const;
        TOptional<FString> GetOrderDirection() const;
        TOptional<FString> GetEntryPeriodEventId() const;
        TOptional<FString> GetAccessPeriodEventId() const;

        static TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateSubscribeRankingModelMasterRequest, ESPMode::ThreadSafe> FUpdateSubscribeRankingModelMasterRequestPtr;
}