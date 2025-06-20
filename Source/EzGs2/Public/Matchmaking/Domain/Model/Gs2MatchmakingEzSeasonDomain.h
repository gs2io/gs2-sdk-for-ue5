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
#include "Matchmaking/Domain/Model/Season.h"
#include "Matchmaking/Model/Gs2MatchmakingEzGathering.h"
#include "Matchmaking/Model/Gs2MatchmakingEzRatingModel.h"
#include "Matchmaking/Model/Gs2MatchmakingEzRating.h"
#include "Matchmaking/Model/Gs2MatchmakingEzJoinedSeasonGathering.h"
#include "Matchmaking/Model/Gs2MatchmakingEzSeasonGathering.h"
#include "Matchmaking/Model/Gs2MatchmakingEzSeasonModel.h"
#include "Matchmaking/Model/Gs2MatchmakingEzPlayer.h"
#include "Matchmaking/Model/Gs2MatchmakingEzAttributeRange.h"
#include "Matchmaking/Model/Gs2MatchmakingEzCapacityOfRole.h"
#include "Matchmaking/Model/Gs2MatchmakingEzAttribute.h"
#include "Matchmaking/Model/Gs2MatchmakingEzGameResult.h"
#include "Matchmaking/Model/Gs2MatchmakingEzBallot.h"
#include "Matchmaking/Model/Gs2MatchmakingEzSignedBallot.h"
#include "Matchmaking/Model/Gs2MatchmakingEzTimeSpan.h"
#include "Gs2MatchmakingEzSeasonGatheringDomain.h"
#include "Gs2MatchmakingEzJoinedSeasonGatheringDomain.h"
#include "Gs2MatchmakingEzSeasonDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    class EZGS2_API FEzSeasonDomain final :
        public TSharedFromThis<FEzSeasonDomain>
    {
        Gs2::Matchmaking::Domain::Model::FSeasonDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> MatchmakingContextToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> SeasonName() const;
        TOptional<int64> Season() const;

        FEzSeasonDomain(
            Gs2::Matchmaking::Domain::Model::FSeasonDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonGatheringDomainPtr SeasonGathering(
            const int64 Tier,
            const FString SeasonGatheringName
        ) const;

        Gs2::UE5::Matchmaking::Domain::Model::FEzJoinedSeasonGatheringDomainPtr JoinedSeasonGathering(
        ) const;

    };
    typedef TSharedPtr<FEzSeasonDomain> FEzSeasonDomainPtr;
}
