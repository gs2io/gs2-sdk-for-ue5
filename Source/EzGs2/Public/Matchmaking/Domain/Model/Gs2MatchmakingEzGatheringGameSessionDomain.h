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
#include "Matchmaking/Domain/Model/GatheringAccessToken.h"
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
#include "Gs2MatchmakingEzGatheringGameSessionDomain.h"
#include "Matchmaking/Domain/Iterator/Gs2MatchmakingEzDoMatchmakingIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    class EZGS2_API FEzGatheringGameSessionDomain final :
        public TSharedFromThis<FEzGatheringGameSessionDomain>
    {
        Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> GatheringName() const;

        FEzGatheringGameSessionDomain(
            Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FUpdateGatheringTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>,
            public TSharedFromThis<FUpdateGatheringTask>
        {
            TSharedPtr<FEzGatheringGameSessionDomain> Self;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges;

        public:
            explicit FUpdateGatheringTask(
                TSharedPtr<FEzGatheringGameSessionDomain> Self,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>> Result
            ) override;
        };
        friend FUpdateGatheringTask;

        TSharedPtr<FAsyncTask<FUpdateGatheringTask>> UpdateGathering(
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>>()
        );

        class FCancelMatchmakingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>,
            public TSharedFromThis<FCancelMatchmakingTask>
        {
            TSharedPtr<FEzGatheringGameSessionDomain> Self;

        public:
            explicit FCancelMatchmakingTask(
                TSharedPtr<FEzGatheringGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>> Result
            ) override;
        };
        friend FCancelMatchmakingTask;

        TSharedPtr<FAsyncTask<FCancelMatchmakingTask>> CancelMatchmaking(
        );

        class FEarlyCompleteMatchmakingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>,
            public TSharedFromThis<FEarlyCompleteMatchmakingTask>
        {
            TSharedPtr<FEzGatheringGameSessionDomain> Self;

        public:
            explicit FEarlyCompleteMatchmakingTask(
                TSharedPtr<FEzGatheringGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>> Result
            ) override;
        };
        friend FEarlyCompleteMatchmakingTask;

        TSharedPtr<FAsyncTask<FEarlyCompleteMatchmakingTask>> EarlyCompleteMatchmaking(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Model::FEzGathering>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzGatheringGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzGatheringGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGatheringPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Matchmaking::Model::FEzGatheringPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzGatheringGameSessionDomain> FEzGatheringGameSessionDomainPtr;
}
