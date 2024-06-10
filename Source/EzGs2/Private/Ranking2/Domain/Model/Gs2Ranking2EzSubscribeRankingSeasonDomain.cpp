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

#include "Ranking2/Domain/Model/Gs2Ranking2EzSubscribeRankingSeasonDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzSubscribeRankingSeasonDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzSubscribeRankingSeasonDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSubscribeRankingSeasonDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzSubscribeRankingSeasonDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<int64> FEzSubscribeRankingSeasonDomain::Season() const
    {
        return Domain->Season;
    }

    FEzSubscribeRankingSeasonDomain::FEzSubscribeRankingSeasonDomain(
        Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingScoreDomainPtr FEzSubscribeRankingSeasonDomain::SubscribeRankingScore(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingScoreDomain>(
            Domain->SubscribeRankingScore(
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingDataDomainPtr FEzSubscribeRankingSeasonDomain::SubscribeRankingData(
        const FString ScorerUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingDataDomain>(
            Domain->SubscribeRankingData(
                ScorerUserId
            ),
            ConnectionValue
        );
    }
}
