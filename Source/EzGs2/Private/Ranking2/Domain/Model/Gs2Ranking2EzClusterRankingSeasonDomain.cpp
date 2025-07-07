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

#include "Ranking2/Domain/Model/Gs2Ranking2EzClusterRankingSeasonDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzClusterRankingSeasonDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzClusterRankingSeasonDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzClusterRankingSeasonDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<FString> FEzClusterRankingSeasonDomain::ClusterName() const
    {
        return Domain->ClusterName;
    }

    TOptional<int64> FEzClusterRankingSeasonDomain::Season() const
    {
        return Domain->Season;
    }

    TOptional<FString> FEzClusterRankingSeasonDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzClusterRankingSeasonDomain::FEzClusterRankingSeasonDomain(
        Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardDomainPtr FEzClusterRankingSeasonDomain::ClusterRankingReceivedReward(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardDomain>(
            Domain->ClusterRankingReceivedReward(
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreDomainPtr FEzClusterRankingSeasonDomain::ClusterRankingScore(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreDomain>(
            Domain->ClusterRankingScore(
            ),
            ConnectionValue
        );
    }
}
