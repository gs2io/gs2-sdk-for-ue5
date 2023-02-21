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
#include "Matchmaking/Domain/Model/RatingAccessToken.h"
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
#include "Gs2MatchmakingEzRatingGameSessionDomain.h"
#include "Matchmaking/Domain/Iterator/Gs2MatchmakingEzDescribeRatingsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    class EZGS2_API FEzRatingGameSessionDomain final :
        public TSharedFromThis<FEzRatingGameSessionDomain>
    {
        Gs2::Matchmaking::Domain::Model::FRatingAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> RatingName() const;

        FEzRatingGameSessionDomain(
            Gs2::Matchmaking::Domain::Model::FRatingAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetRatingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Model::FEzRating>,
            public TSharedFromThis<FGetRatingTask>
        {
            TSharedPtr<FEzRatingGameSessionDomain> Self;

        public:
            explicit FGetRatingTask(
                TSharedPtr<FEzRatingGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzRating>> Result
            ) override;
        };
        friend FGetRatingTask;

        TSharedPtr<FAsyncTask<FGetRatingTask>> GetRating(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Model::FEzRating>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzRatingGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzRatingGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzRatingPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzRatingGameSessionDomain> FEzRatingGameSessionDomainPtr;
}
