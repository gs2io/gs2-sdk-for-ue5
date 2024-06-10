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

#include "Ranking2/Domain/Model/Gs2Ranking2EzUserDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzUserDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzUserDomain::FEzUserDomain(
        Gs2::Ranking2::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreDomainPtr FEzUserDomain::GlobalRankingScore(
        const FString RankingName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreDomain>(
            Domain->GlobalRankingScore(
                RankingName,
                Season
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingSeasonDomainPtr FEzUserDomain::SubscribeRankingSeason(
        const FString RankingName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingSeasonDomain>(
            Domain->SubscribeRankingSeason(
                RankingName,
                Season
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeDomainPtr FEzUserDomain::Subscribe(
        const FString RankingName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeDomain>(
            Domain->Subscribe(
                RankingName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingReceivedRewardDomainPtr FEzUserDomain::GlobalRankingReceivedReward(
        const FString RankingName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingReceivedRewardDomain>(
            Domain->GlobalRankingReceivedReward(
                RankingName,
                Season
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardDomainPtr FEzUserDomain::ClusterRankingReceivedReward(
        const FString RankingName,
        const FString ClusterName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardDomain>(
            Domain->ClusterRankingReceivedReward(
                RankingName,
                ClusterName,
                Season
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreDomainPtr FEzUserDomain::ClusterRankingScore(
        const FString RankingName,
        const FString ClusterName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreDomain>(
            Domain->ClusterRankingScore(
                RankingName,
                ClusterName,
                Season
            ),
            ConnectionValue
        );
    }
}
