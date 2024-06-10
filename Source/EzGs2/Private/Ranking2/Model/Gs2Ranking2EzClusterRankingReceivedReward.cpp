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

#include "Ranking2/Model/Gs2Ranking2EzClusterRankingReceivedReward.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzClusterRankingReceivedReward> FEzClusterRankingReceivedReward::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingReceivedReward> FEzClusterRankingReceivedReward::WithClusterName(
        const TOptional<FString> ClusterName
    )
    {
        this->ClusterNameValue = ClusterName;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingReceivedReward> FEzClusterRankingReceivedReward::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingReceivedReward> FEzClusterRankingReceivedReward::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingReceivedReward> FEzClusterRankingReceivedReward::WithReceivedAt(
        const TOptional<int64> ReceivedAt
    )
    {
        this->ReceivedAtValue = ReceivedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzClusterRankingReceivedReward::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<FString> FEzClusterRankingReceivedReward::GetClusterName() const
    {
        return ClusterNameValue;
    }
    TOptional<int64> FEzClusterRankingReceivedReward::GetSeason() const
    {
        return SeasonValue;
    }

    FString FEzClusterRankingReceivedReward::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<FString> FEzClusterRankingReceivedReward::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FEzClusterRankingReceivedReward::GetReceivedAt() const
    {
        return ReceivedAtValue;
    }

    FString FEzClusterRankingReceivedReward::GetReceivedAtString() const
    {
        if (!ReceivedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ReceivedAtValue.GetValue());
    }

    Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr FEzClusterRankingReceivedReward::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FClusterRankingReceivedReward>()
            ->WithRankingName(RankingNameValue)
            ->WithClusterName(ClusterNameValue)
            ->WithSeason(SeasonValue)
            ->WithUserId(UserIdValue)
            ->WithReceivedAt(ReceivedAtValue);
    }

    TSharedPtr<FEzClusterRankingReceivedReward> FEzClusterRankingReceivedReward::FromModel(const Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzClusterRankingReceivedReward>()
            ->WithRankingName(Model->GetRankingName())
            ->WithClusterName(Model->GetClusterName())
            ->WithSeason(Model->GetSeason())
            ->WithUserId(Model->GetUserId())
            ->WithReceivedAt(Model->GetReceivedAt());
    }
}