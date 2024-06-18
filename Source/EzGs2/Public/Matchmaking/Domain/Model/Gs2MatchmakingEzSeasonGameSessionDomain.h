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
#include "Matchmaking/Domain/Model/SeasonAccessToken.h"
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
#include "Gs2MatchmakingEzSeasonGatheringGameSessionDomain.h"
#include "Matchmaking/Domain/Iterator/Gs2MatchmakingEzDoSeasonMatchmakingIterator.h"
#include "Gs2MatchmakingEzJoinedSeasonGatheringGameSessionDomain.h"
#include "Matchmaking/Domain/Iterator/Gs2MatchmakingEzDescribeJoinedSeasonGatheringsIterator.h"
#include "Gs2MatchmakingEzSeasonGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    class EZGS2_API FEzSeasonGameSessionDomain final :
        public TSharedFromThis<FEzSeasonGameSessionDomain>
    {
        Gs2::Matchmaking::Domain::Model::FSeasonAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> MatchmakingContextToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> SeasonName() const;
        TOptional<int64> Season() const;

        FEzSeasonGameSessionDomain(
            Gs2::Matchmaking::Domain::Model::FSeasonAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Matchmaking::Domain::Iterator::FEzDoSeasonMatchmakingIteratorPtr DoSeasonMatchmaking(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDoSeasonMatchmaking(TFunction<void()> Callback);

        void UnsubscribeDoSeasonMatchmaking(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonGatheringGameSessionDomainPtr SeasonGathering(
            const int64 Tier,
            const FString SeasonGatheringName
        ) const;

        Gs2::UE5::Matchmaking::Domain::Iterator::FEzDescribeJoinedSeasonGatheringsIteratorPtr JoinedSeasonGatherings(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeJoinedSeasonGatherings(TFunction<void()> Callback);

        void UnsubscribeJoinedSeasonGatherings(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Matchmaking::Domain::Model::FEzJoinedSeasonGatheringGameSessionDomainPtr JoinedSeasonGathering(
        ) const;

    };
    typedef TSharedPtr<FEzSeasonGameSessionDomain> FEzSeasonGameSessionDomainPtr;
}
