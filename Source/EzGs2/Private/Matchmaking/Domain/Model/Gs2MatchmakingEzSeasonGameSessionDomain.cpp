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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzSeasonGameSessionDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzSeasonGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzSeasonGameSessionDomain::MatchmakingContextToken() const
    {
        return Domain->MatchmakingContextToken;
    }

    TOptional<FString> FEzSeasonGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSeasonGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzSeasonGameSessionDomain::SeasonName() const
    {
        return Domain->SeasonName;
    }

    TOptional<int64> FEzSeasonGameSessionDomain::Season() const
    {
        return Domain->Season;
    }

    FEzSeasonGameSessionDomain::FEzSeasonGameSessionDomain(
        Gs2::Matchmaking::Domain::Model::FSeasonAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzJoinedSeasonGatheringGameSessionDomainPtr FEzSeasonGameSessionDomain::JoinedSeasonGathering(
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzJoinedSeasonGatheringGameSessionDomain>(
            Domain->JoinedSeasonGathering(
            ),
            GameSession,
            ConnectionValue
        );
    }
}
