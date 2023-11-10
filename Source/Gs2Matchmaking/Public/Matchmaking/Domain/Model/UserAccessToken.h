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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Matchmaking/Gs2Matchmaking.h"
#include "Matchmaking/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingByPlayerIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingIterator.h"
#include "Matchmaking/Domain/Iterator/DoMatchmakingByUserIdIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingModelMastersIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingModelsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeRatingsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Matchmaking::Domain
{
    class FGs2MatchmakingDomain;
    typedef TSharedPtr<FGs2MatchmakingDomain> FGs2MatchmakingDomainPtr;
}

namespace Gs2::Matchmaking::Domain::Model
{
    class FNamespaceDomain;
    class FGatheringDomain;
    class FGatheringAccessTokenDomain;
    class FRatingModelMasterDomain;
    class FRatingModelDomain;
    class FCurrentRatingModelMasterDomain;
    class FRatingDomain;
    class FRatingAccessTokenDomain;
    class FBallotDomain;
    class FBallotAccessTokenDomain;
    class FVoteDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2MATCHMAKING_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr Service;
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> MatchmakingContextToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> GetMatchmakingContextToken() const
        {
            return MatchmakingContextToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2MATCHMAKING_API FCreateGatheringTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>,
            public TSharedFromThis<FCreateGatheringTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FCreateGatheringRequestPtr Request;
        public:
            explicit FCreateGatheringTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FCreateGatheringRequestPtr Request
            );

            FCreateGatheringTask(
                const FCreateGatheringTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>> Result
            ) override;
        };
        friend FCreateGatheringTask;

        TSharedPtr<FAsyncTask<FCreateGatheringTask>> CreateGathering(
            Request::FCreateGatheringRequestPtr Request
        );

        Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingIteratorPtr DoMatchmaking(
            const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player
        ) const;

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain> Gathering(
            const FString GatheringName
        );

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotAccessTokenDomain> Ballot(
            const FString RatingName,
            const FString GatheringName,
            const int32 NumberOfPlayer,
            const FString KeyId
        );

        Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIteratorPtr Ratings(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRatings(
            TFunction<void()> Callback
        );

        void UnsubscribeRatings(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingAccessTokenDomain> Rating(
            const FString RatingName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
