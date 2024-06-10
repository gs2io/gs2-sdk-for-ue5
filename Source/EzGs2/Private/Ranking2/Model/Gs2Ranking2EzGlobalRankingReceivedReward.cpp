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

#include "Ranking2/Model/Gs2Ranking2EzGlobalRankingReceivedReward.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzGlobalRankingReceivedReward> FEzGlobalRankingReceivedReward::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingReceivedReward> FEzGlobalRankingReceivedReward::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingReceivedReward> FEzGlobalRankingReceivedReward::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingReceivedReward> FEzGlobalRankingReceivedReward::WithReceivedAt(
        const TOptional<int64> ReceivedAt
    )
    {
        this->ReceivedAtValue = ReceivedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzGlobalRankingReceivedReward::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<int64> FEzGlobalRankingReceivedReward::GetSeason() const
    {
        return SeasonValue;
    }

    FString FEzGlobalRankingReceivedReward::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<FString> FEzGlobalRankingReceivedReward::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FEzGlobalRankingReceivedReward::GetReceivedAt() const
    {
        return ReceivedAtValue;
    }

    FString FEzGlobalRankingReceivedReward::GetReceivedAtString() const
    {
        if (!ReceivedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ReceivedAtValue.GetValue());
    }

    Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr FEzGlobalRankingReceivedReward::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FGlobalRankingReceivedReward>()
            ->WithRankingName(RankingNameValue)
            ->WithSeason(SeasonValue)
            ->WithUserId(UserIdValue)
            ->WithReceivedAt(ReceivedAtValue);
    }

    TSharedPtr<FEzGlobalRankingReceivedReward> FEzGlobalRankingReceivedReward::FromModel(const Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGlobalRankingReceivedReward>()
            ->WithRankingName(Model->GetRankingName())
            ->WithSeason(Model->GetSeason())
            ->WithUserId(Model->GetUserId())
            ->WithReceivedAt(Model->GetReceivedAt());
    }
}