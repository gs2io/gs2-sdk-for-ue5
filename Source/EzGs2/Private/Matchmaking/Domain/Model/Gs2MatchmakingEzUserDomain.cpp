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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzUserDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzUserDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserDomain::MatchmakingContextToken() const
    {
        return Domain->MatchmakingContextToken;
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
        Gs2::Matchmaking::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringDomainPtr FEzUserDomain::Gathering(
        const FString GatheringName
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringDomain>(
            Domain->Gathering(
                GatheringName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomainPtr FEzUserDomain::Ballot(
        const FString RatingName,
        const FString GatheringName,
        const int32 NumberOfPlayer,
        const FString KeyId
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomain>(
            Domain->Ballot(
                RatingName,
                GatheringName,
                NumberOfPlayer,
                KeyId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Matchmaking::Domain::Model::FEzRatingDomainPtr FEzUserDomain::Rating(
        const FString RatingName
    ) const
    {
        return MakeShared<Gs2::UE5::Matchmaking::Domain::Model::FEzRatingDomain>(
            Domain->Rating(
                RatingName
            ),
            ProfileValue
        );
    }
}
