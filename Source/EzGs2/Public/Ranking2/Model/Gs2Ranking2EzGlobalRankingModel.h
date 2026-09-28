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
#include "Ranking2/Model/GlobalRankingModel.h"
#include "Gs2Ranking2EzRankingReward.h"

namespace Gs2::UE5::Ranking2::Model
{
	class EZGS2_API FEzGlobalRankingModel final : public TSharedFromThis<FEzGlobalRankingModel>
	{
        TOptional<FString> GlobalRankingModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<bool> SumValue;
        TOptional<FString> OrderDirectionValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzRankingReward>>> RankingRewardsValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TOptional<FString> AccessPeriodEventIdValue;

	public:
        TSharedPtr<FEzGlobalRankingModel> WithGlobalRankingModelId(const TOptional<FString> GlobalRankingModelId);
        TSharedPtr<FEzGlobalRankingModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzGlobalRankingModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzGlobalRankingModel> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FEzGlobalRankingModel> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FEzGlobalRankingModel> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FEzGlobalRankingModel> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FEzGlobalRankingModel> WithRankingRewards(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzRankingReward>>> RankingRewards);
        TSharedPtr<FEzGlobalRankingModel> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FEzGlobalRankingModel> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);

        TOptional<FString> GetGlobalRankingModelId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetMinimumValue() const;
        FString GetMinimumValueString() const;

        TOptional<int64> GetMaximumValue() const;
        FString GetMaximumValueString() const;

        TOptional<bool> GetSum() const;
        FString GetSumString() const;

        TOptional<FString> GetOrderDirection() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzRankingReward>>> GetRankingRewards() const;

        TOptional<FString> GetEntryPeriodEventId() const;

        TOptional<FString> GetAccessPeriodEventId() const;

        Gs2::Ranking2::Model::FGlobalRankingModelPtr ToModel() const;
        static TSharedPtr<FEzGlobalRankingModel> FromModel(Gs2::Ranking2::Model::FGlobalRankingModelPtr Model);
    };
    typedef TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModelPtr;
}