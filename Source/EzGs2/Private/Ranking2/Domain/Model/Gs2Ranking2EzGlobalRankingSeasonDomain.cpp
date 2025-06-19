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
 *
 * deny overwrite
 */

#include "Ranking2/Domain/Model/Gs2Ranking2EzGlobalRankingSeasonDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzGlobalRankingSeasonDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzGlobalRankingSeasonDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzGlobalRankingSeasonDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<int64> FEzGlobalRankingSeasonDomain::Season() const
    {
        return Domain->Season;
    }

    FEzGlobalRankingSeasonDomain::FEzGlobalRankingSeasonDomain(
        Gs2::Ranking2::Domain::Model::FGlobalRankingSeasonDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreDomainPtr FEzGlobalRankingSeasonDomain::GlobalRankingScore(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreDomain>(
            Domain->GlobalRankingScore(
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingDataDomainPtr FEzGlobalRankingSeasonDomain::GlobalRankingData(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingDataDomain>(
            Domain->GlobalRankingData(
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingReceivedRewardDomainPtr FEzGlobalRankingSeasonDomain::GlobalRankingReceivedReward(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingReceivedRewardDomain>(
            Domain->GlobalRankingReceivedReward(
            ),
            ConnectionValue
        );
    }
}
