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

    class GS2MATCHMAKING_API FUserDomain:
        public TSharedFromThis<FUserDomain>
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
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2MATCHMAKING_API FCreateGatheringTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FGatheringDomain>,
            public TSharedFromThis<FCreateGatheringTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FCreateGatheringByUserIdRequestPtr Request;
        public:
            explicit FCreateGatheringTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FCreateGatheringByUserIdRequestPtr Request
            );

            FCreateGatheringTask(
                const FCreateGatheringTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain>> Result
            ) override;
        };
        friend FCreateGatheringTask;

        TSharedPtr<FAsyncTask<FCreateGatheringTask>> CreateGathering(
            Request::FCreateGatheringByUserIdRequestPtr Request
        );

        class GS2MATCHMAKING_API FDeleteGatheringTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FGatheringDomain>,
            public TSharedFromThis<FDeleteGatheringTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FDeleteGatheringRequestPtr Request;
        public:
            explicit FDeleteGatheringTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FDeleteGatheringRequestPtr Request
            );

            FDeleteGatheringTask(
                const FDeleteGatheringTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain>> Result
            ) override;
        };
        friend FDeleteGatheringTask;

        TSharedPtr<FAsyncTask<FDeleteGatheringTask>> DeleteGathering(
            Request::FDeleteGatheringRequestPtr Request
        );

        class GS2MATCHMAKING_API FPutResultTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingDomain>>>,
            public TSharedFromThis<FPutResultTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FPutResultRequestPtr Request;
        public:
            explicit FPutResultTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FPutResultRequestPtr Request
            );

            FPutResultTask(
                const FPutResultTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingDomain>>>> Result
            ) override;
        };
        friend FPutResultTask;

        TSharedPtr<FAsyncTask<FPutResultTask>> PutResult(
            Request::FPutResultRequestPtr Request
        );

        Gs2::Matchmaking::Domain::Iterator::FDescribeGatheringsIteratorPtr Gatherings(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGatherings(
            TFunction<void()> Callback
        );

        void UnsubscribeGatherings(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByPlayerIteratorPtr DoMatchmakingByPlayer(
            const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player
        ) const;

        Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByUserIdIteratorPtr DoMatchmaking(
            const TSharedPtr<Gs2::Matchmaking::Model::FPlayer> Player
        ) const;

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringDomain> Gathering(
            const FString GatheringName
        );

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FBallotDomain> Ballot(
            const FString RatingName,
            const FString GatheringName,
            const int32 NumberOfPlayer,
            const FString KeyId
        );

        Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsByUserIdIteratorPtr Ratings(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRatings(
            TFunction<void()> Callback
        );

        void UnsubscribeRatings(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingDomain> Rating(
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

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
