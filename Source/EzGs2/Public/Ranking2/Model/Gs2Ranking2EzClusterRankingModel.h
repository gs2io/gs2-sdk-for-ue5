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
#include "Ranking2/Model/ClusterRankingModel.h"
#include "Gs2Ranking2EzRankingReward.h"

namespace Gs2::UE5::Ranking2::Model
{
	class EZGS2_API FEzClusterRankingModel final : public TSharedFromThis<FEzClusterRankingModel>
	{
        TOptional<FString> ClusterRankingModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ClusterTypeValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzRankingReward>>> RankingRewardsValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;

	public:
        TSharedPtr<FEzClusterRankingModel> WithClusterRankingModelId(const TOptional<FString> ClusterRankingModelId);
        TSharedPtr<FEzClusterRankingModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzClusterRankingModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzClusterRankingModel> WithClusterType(const TOptional<FString> ClusterType);
        TSharedPtr<FEzClusterRankingModel> WithRankingRewards(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzRankingReward>>> RankingRewards);
        TSharedPtr<FEzClusterRankingModel> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FEzClusterRankingModel> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);

        TOptional<FString> GetClusterRankingModelId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetClusterType() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzRankingReward>>> GetRankingRewards() const;

        TOptional<FString> GetEntryPeriodEventId() const;

        TOptional<FString> GetAccessPeriodEventId() const;

        Gs2::Ranking2::Model::FClusterRankingModelPtr ToModel() const;
        static TSharedPtr<FEzClusterRankingModel> FromModel(Gs2::Ranking2::Model::FClusterRankingModelPtr Model);
    };
    typedef TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModelPtr;
}