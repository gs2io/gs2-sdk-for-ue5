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
#include "Matchmaking/Domain/Model/UserAccessToken.h"
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
#include "Gs2MatchmakingEzRatingGameSessionDomain.h"
#include "Matchmaking/Domain/Iterator/Gs2MatchmakingEzDescribeRatingsIterator.h"
#include "Gs2MatchmakingEzBallotGameSessionDomain.h"
#include "Gs2MatchmakingEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Matchmaking::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> MatchmakingContextToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Matchmaking::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FCreateGatheringTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>,
            public TSharedFromThis<FCreateGatheringTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            Gs2::UE5::Matchmaking::Model::FEzPlayerPtr Player;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>> CapacityOfRoles;
            TOptional<TArray<FString>> AllowUserIds;
            TOptional<int64> ExpiresAt;
            Gs2::UE5::Matchmaking::Model::FEzTimeSpanPtr ExpiresAtTimeSpan;

        public:
            explicit FCreateGatheringTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                Gs2::UE5::Matchmaking::Model::FEzPlayerPtr Player,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>>(),
                TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>> CapacityOfRoles = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>>(),
                TOptional<TArray<FString>> AllowUserIds = TOptional<TArray<FString>>(),
                TOptional<int64> ExpiresAt = TOptional<int64>(),
                Gs2::UE5::Matchmaking::Model::FEzTimeSpanPtr ExpiresAtTimeSpan = nullptr
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomain>> Result
            ) override;
        };
        friend FCreateGatheringTask;

        TSharedPtr<FAsyncTask<FCreateGatheringTask>> CreateGathering(
            Gs2::UE5::Matchmaking::Model::FEzPlayerPtr Player,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>> CapacityOfRoles = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>>(),
            TOptional<TArray<FString>> AllowUserIds = TOptional<TArray<FString>>(),
            TOptional<int64> ExpiresAt = TOptional<int64>(),
            Gs2::UE5::Matchmaking::Model::FEzTimeSpanPtr ExpiresAtTimeSpan = nullptr
        );

        Gs2::UE5::Matchmaking::Domain::Iterator::FEzDoMatchmakingIteratorPtr DoMatchmaking(
            const Gs2::UE5::Matchmaking::Model::FEzPlayerPtr Player
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDoMatchmaking(TFunction<void()> Callback);

        void UnsubscribeDoMatchmaking(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Matchmaking::Domain::Model::FEzGatheringGameSessionDomainPtr Gathering(
            const FString GatheringName
        ) const;

        Gs2::UE5::Matchmaking::Domain::Iterator::FEzDescribeRatingsIteratorPtr Ratings(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRatings(TFunction<void()> Callback);

        void UnsubscribeRatings(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Matchmaking::Domain::Model::FEzRatingGameSessionDomainPtr Rating(
            const FString RatingName
        ) const;

        Gs2::UE5::Matchmaking::Domain::Model::FEzBallotGameSessionDomainPtr Ballot(
            const FString RatingName,
            const FString GatheringName,
            const int32 NumberOfPlayer,
            const FString KeyId
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
