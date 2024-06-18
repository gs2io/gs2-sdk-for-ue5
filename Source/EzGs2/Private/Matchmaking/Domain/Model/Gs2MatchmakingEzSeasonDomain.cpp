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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzSeasonDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzSeasonDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzSeasonDomain::MatchmakingContextToken() const
    {
        return Domain->MatchmakingContextToken;
    }

    TOptional<FString> FEzSeasonDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSeasonDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzSeasonDomain::SeasonName() const
    {
        return Domain->SeasonName;
    }

    TOptional<int64> FEzSeasonDomain::Season() const
    {
        return Domain->Season;
    }

    FEzSeasonDomain::FEzSeasonDomain(
        Gs2::Matchmaking::Domain::Model::FSeasonDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonGatheringDomainPtr FEzSeasonDomain::SeasonGathering(
        const int64 Tier,
        const FString SeasonGatheringName
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonGatheringDomain>(
            Domain->SeasonGathering(
                Tier,
                SeasonGatheringName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzJoinedSeasonGatheringDomainPtr FEzSeasonDomain::JoinedSeasonGathering(
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzJoinedSeasonGatheringDomain>(
            Domain->JoinedSeasonGathering(
            ),
            ConnectionValue
        );
    }
}
