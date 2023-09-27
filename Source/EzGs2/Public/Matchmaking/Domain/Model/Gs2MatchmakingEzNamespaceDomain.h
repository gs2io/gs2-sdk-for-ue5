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
#include "Matchmaking/Domain/Model/Namespace.h"
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
#include "Gs2MatchmakingEzUserDomain.h"
#include "Gs2MatchmakingEzUserDomain.h"
#include "Gs2MatchmakingEzUserGameSessionDomain.h"
#include "Gs2MatchmakingEzRatingModelDomain.h"
#include "Matchmaking/Domain/Iterator/Gs2MatchmakingEzDescribeRatingModelsIterator.h"
#include "Gs2MatchmakingEzNamespaceDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Matchmaking::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Matchmaking::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FVoteTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomain>,
            public TSharedFromThis<FVoteTask>
        {
            TSharedPtr<FEzNamespaceDomain> Self;
            FString BallotBody;
            FString BallotSignature;
            FString KeyId;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>> GameResults;

        public:
            explicit FVoteTask(
                TSharedPtr<FEzNamespaceDomain> Self,
                FString BallotBody,
                FString BallotSignature,
                FString KeyId,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>> GameResults = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomain>> Result
            ) override;
        };
        friend FVoteTask;

        TSharedPtr<FAsyncTask<FVoteTask>> Vote(
            FString BallotBody,
            FString BallotSignature,
            FString KeyId,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>> GameResults = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>>()
        );

        class FVoteMultipleTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomain>,
            public TSharedFromThis<FVoteMultipleTask>
        {
            TSharedPtr<FEzNamespaceDomain> Self;
            FString KeyId;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzSignedBallot>>> SignedBallots;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>> GameResults;

        public:
            explicit FVoteMultipleTask(
                TSharedPtr<FEzNamespaceDomain> Self,
                FString KeyId,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzSignedBallot>>> SignedBallots = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzSignedBallot>>>(),
                TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>> GameResults = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomain>> Result
            ) override;
        };
        friend FVoteMultipleTask;

        TSharedPtr<FAsyncTask<FVoteMultipleTask>> VoteMultiple(
            FString KeyId,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzSignedBallot>>> SignedBallots = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzSignedBallot>>>(),
            TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>> GameResults = TOptional<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGameResult>>>()
        );

        Gs2::UE5::Matchmaking::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Matchmaking::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        ) const;

        Gs2::UE5::Matchmaking::Domain::Iterator::FEzDescribeRatingModelsIteratorPtr RatingModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRatingModels(TFunction<void()> Callback);

        void UnsubscribeRatingModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Matchmaking::Domain::Model::FEzRatingModelDomainPtr RatingModel(
            const FString RatingName
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
