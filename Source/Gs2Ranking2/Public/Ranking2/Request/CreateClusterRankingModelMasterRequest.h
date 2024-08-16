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
#include "Dom/JsonObject.h"
#include "../Model/RankingReward.h"

namespace Gs2::Ranking2::Request
{
    class FCreateClusterRankingModelMasterRequest;

    class GS2RANKING2_API FCreateClusterRankingModelMasterRequest final : public TSharedFromThis<FCreateClusterRankingModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ClusterTypeValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<bool> SumValue;
        TOptional<int32> ScoreTtlDaysValue;
        TOptional<FString> OrderDirectionValue;
        TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> RankingRewardsValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;
        
    public:
        
        FCreateClusterRankingModelMasterRequest();
        FCreateClusterRankingModelMasterRequest(
            const FCreateClusterRankingModelMasterRequest& From
        );
        ~FCreateClusterRankingModelMasterRequest() = default;

        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithClusterType(const TOptional<FString> ClusterType);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithScoreTtlDays(const TOptional<int32> ScoreTtlDays);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithRankingRewards(const TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> RankingRewards);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FCreateClusterRankingModelMasterRequest> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetClusterType() const;
        TOptional<int64> GetMinimumValue() const;
        FString GetMinimumValueString() const;
        TOptional<int64> GetMaximumValue() const;
        FString GetMaximumValueString() const;
        TOptional<bool> GetSum() const;
        FString GetSumString() const;
        TOptional<int32> GetScoreTtlDays() const;
        FString GetScoreTtlDaysString() const;
        TOptional<FString> GetOrderDirection() const;TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> GetRankingRewards() const;
        TOptional<FString> GetEntryPeriodEventId() const;
        TOptional<FString> GetAccessPeriodEventId() const;

        static TSharedPtr<FCreateClusterRankingModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateClusterRankingModelMasterRequest> FCreateClusterRankingModelMasterRequestPtr;
}