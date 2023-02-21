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
#include "Matchmaking/Domain/Model/BallotAccessToken.h"
#include "Matchmaking/Model/Gs2MatchmakingEzGathering.h"
#include "Matchmaking/Model/Gs2MatchmakingEzRatingModel.h"
#include "Matchmaking/Model/Gs2MatchmakingEzAttributeRange.h"
#include "Matchmaking/Model/Gs2MatchmakingEzCapacityOfRole.h"
#include "Matchmaking/Model/Gs2MatchmakingEzAttribute.h"
#include "Matchmaking/Model/Gs2MatchmakingEzPlayer.h"
#include "Matchmaking/Model/Gs2MatchmakingEzRating.h"
#include "Matchmaking/Model/Gs2MatchmakingEzGameResult.h"
#include "Matchmaking/Model/Gs2MatchmakingEzBallot.h"
#include "Matchmaking/Model/Gs2MatchmakingEzSignedBallot.h"
#include "Matchmaking/Model/Gs2MatchmakingEzTimeSpan.h"
#include "Gs2MatchmakingEzBallotGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    class EZGS2_API FEzBallotGameSessionDomain final :
        public TSharedFromThis<FEzBallotGameSessionDomain>
    {
        Gs2::Matchmaking::Domain::Model::FBallotAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> RatingName() const;
        TOptional<FString> GatheringName() const;
        TOptional<int32> NumberOfPlayer() const;
        TOptional<FString> KeyId() const;

        FEzBallotGameSessionDomain(
            Gs2::Matchmaking::Domain::Model::FBallotAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FCreateVoteTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotGameSessionDomain>,
            public TSharedFromThis<FCreateVoteTask>
        {
            TSharedPtr<FEzBallotGameSessionDomain> Self;

        public:
            explicit FCreateVoteTask(
                TSharedPtr<FEzBallotGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotGameSessionDomain>> Result
            ) override;
        };
        friend FCreateVoteTask;

        TSharedPtr<FAsyncTask<FCreateVoteTask>> CreateVote(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Model::FEzBallot>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzBallotGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzBallotGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzBallotPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzBallotGameSessionDomain> FEzBallotGameSessionDomainPtr;
}
