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
#include "Ranking2/Model/RankingReward.h"
#include "Gs2Ranking2EzAcquireAction.h"

namespace Gs2::UE5::Ranking2::Model
{
	class EZGS2_API FEzRankingReward final : public TSharedFromThis<FEzRankingReward>
	{
        TOptional<int32> ThresholdRankValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzAcquireAction>>> AcquireActionsValue;

	public:
        TSharedPtr<FEzRankingReward> WithThresholdRank(const TOptional<int32> ThresholdRank);
        TSharedPtr<FEzRankingReward> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzRankingReward> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzAcquireAction>>> AcquireActions);

        TOptional<int32> GetThresholdRank() const;
        FString GetThresholdRankString() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzAcquireAction>>> GetAcquireActions() const;

        Gs2::Ranking2::Model::FRankingRewardPtr ToModel() const;
        static TSharedPtr<FEzRankingReward> FromModel(Gs2::Ranking2::Model::FRankingRewardPtr Model);
    };
    typedef TSharedPtr<FEzRankingReward> FEzRankingRewardPtr;
}