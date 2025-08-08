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
    class FUpdateClusterRankingModelMasterRequest;

    class GS2RANKING2_API FUpdateClusterRankingModelMasterRequest final : public TSharedFromThis<FUpdateClusterRankingModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ClusterTypeValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<bool> SumValue;
        TOptional<FString> OrderDirectionValue;
        TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> RankingRewardsValue;
        TOptional<FString> RewardCalculationIndexValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;
        
    public:
        
        FUpdateClusterRankingModelMasterRequest();
        FUpdateClusterRankingModelMasterRequest(
            const FUpdateClusterRankingModelMasterRequest& From
        );
        ~FUpdateClusterRankingModelMasterRequest() = default;

        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithClusterType(const TOptional<FString> ClusterType);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithRankingRewards(const TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> RankingRewards);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithRewardCalculationIndex(const TOptional<FString> RewardCalculationIndex);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FUpdateClusterRankingModelMasterRequest> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetClusterType() const;
        TOptional<int64> GetMinimumValue() const;
        FString GetMinimumValueString() const;
        TOptional<int64> GetMaximumValue() const;
        FString GetMaximumValueString() const;
        TOptional<bool> GetSum() const;
        FString GetSumString() const;
        TOptional<FString> GetOrderDirection() const;TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> GetRankingRewards() const;
        TOptional<FString> GetRewardCalculationIndex() const;
        TOptional<FString> GetEntryPeriodEventId() const;
        TOptional<FString> GetAccessPeriodEventId() const;

        static TSharedPtr<FUpdateClusterRankingModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequestPtr;
}