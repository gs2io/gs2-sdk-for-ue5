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
#include "RankingReward.h"

namespace Gs2::Ranking2::Model
{
    class GS2RANKING2_API FClusterRankingModel final : public FGs2Object, public TSharedFromThis<FClusterRankingModel>
    {
        TOptional<FString> ClusterRankingModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ClusterTypeValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<bool> SumValue;
        TOptional<FString> OrderDirectionValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TSharedPtr<TArray<TSharedPtr<FRankingReward>>> RankingRewardsValue;
        TOptional<FString> AccessPeriodEventIdValue;
        TOptional<FString> RewardCalculationIndexValue;

    public:
        FClusterRankingModel();
        FClusterRankingModel(
            const FClusterRankingModel& From
        );
        virtual ~FClusterRankingModel() override = default;

        TSharedPtr<FClusterRankingModel> WithClusterRankingModelId(const TOptional<FString> ClusterRankingModelId);
        TSharedPtr<FClusterRankingModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FClusterRankingModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FClusterRankingModel> WithClusterType(const TOptional<FString> ClusterType);
        TSharedPtr<FClusterRankingModel> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FClusterRankingModel> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FClusterRankingModel> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FClusterRankingModel> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FClusterRankingModel> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FClusterRankingModel> WithRankingRewards(const TSharedPtr<TArray<TSharedPtr<FRankingReward>>> RankingRewards);
        TSharedPtr<FClusterRankingModel> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);
        TSharedPtr<FClusterRankingModel> WithRewardCalculationIndex(const TOptional<FString> RewardCalculationIndex);

        TOptional<FString> GetClusterRankingModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetClusterType() const;
        TOptional<int64> GetMinimumValue() const;
        FString GetMinimumValueString() const;
        TOptional<int64> GetMaximumValue() const;
        FString GetMaximumValueString() const;
        TOptional<bool> GetSum() const;
        FString GetSumString() const;
        TOptional<FString> GetOrderDirection() const;
        TOptional<FString> GetEntryPeriodEventId() const;
        TSharedPtr<TArray<TSharedPtr<FRankingReward>>> GetRankingRewards() const;
        TOptional<FString> GetAccessPeriodEventId() const;
        TOptional<FString> GetRewardCalculationIndex() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRankingNameFromGrn(const FString Grn);

        static TSharedPtr<FClusterRankingModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FClusterRankingModel, ESPMode::ThreadSafe> FClusterRankingModelPtr;
}