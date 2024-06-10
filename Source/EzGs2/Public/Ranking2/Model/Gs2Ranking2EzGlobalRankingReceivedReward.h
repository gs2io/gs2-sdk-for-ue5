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
#include "Ranking2/Model/GlobalRankingReceivedReward.h"

namespace Gs2::UE5::Ranking2::Model
{
	class EZGS2_API FEzGlobalRankingReceivedReward final : public TSharedFromThis<FEzGlobalRankingReceivedReward>
	{
        TOptional<FString> RankingNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> ReceivedAtValue;

	public:
        TSharedPtr<FEzGlobalRankingReceivedReward> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FEzGlobalRankingReceivedReward> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FEzGlobalRankingReceivedReward> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzGlobalRankingReceivedReward> WithReceivedAt(const TOptional<int64> ReceivedAt);

        TOptional<FString> GetRankingName() const;

        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        TOptional<FString> GetUserId() const;

        TOptional<int64> GetReceivedAt() const;
        FString GetReceivedAtString() const;

        Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr ToModel() const;
        static TSharedPtr<FEzGlobalRankingReceivedReward> FromModel(Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr Model);
    };
    typedef TSharedPtr<FEzGlobalRankingReceivedReward> FEzGlobalRankingReceivedRewardPtr;
}