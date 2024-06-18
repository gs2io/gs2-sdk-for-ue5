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
#include "Matchmaking/Domain/Iterator/DescribeSeasonModelsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeSeasonModelMastersIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeSeasonGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeMatchmakingSeasonGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DoSeasonMatchmakingIterator.h"
#include "Matchmaking/Domain/Iterator/DoSeasonMatchmakingByUserIdIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeJoinedSeasonGatheringsIterator.h"
#include "Matchmaking/Domain/Iterator/DescribeJoinedSeasonGatheringsByUserIdIterator.h"
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
    class FCurrentModelMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FSeasonDomain;
    class FSeasonAccessTokenDomain;
    class FSeasonModelDomain;
    class FSeasonModelMasterDomain;
    class FSeasonGatheringDomain;
    class FSeasonGatheringAccessTokenDomain;
    class FJoinedSeasonGatheringDomain;
    class FJoinedSeasonGatheringAccessTokenDomain;
    class FRatingDomain;
    class FRatingAccessTokenDomain;
    class FBallotDomain;
    class FBallotAccessTokenDomain;
    class FVoteDomain;

    class GS2MATCHMAKING_API FSeasonGatheringDomain:
        public TSharedFromThis<FSeasonGatheringDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr Service;
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> SeasonName;
        TOptional<int64> Season;
        TOptional<int64> Tier;
        TOptional<FString> SeasonGatheringName;
    private:

        FString ParentKey;

    public:

        FSeasonGatheringDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> SeasonName,
            const TOptional<int64> Season,
            const TOptional<int64> Tier,
            const TOptional<FString> SeasonGatheringName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSeasonGatheringDomain(
            const FSeasonGatheringDomain& From
        );

        class GS2MATCHMAKING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FSeasonGathering>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FSeasonGatheringDomain> Self;
            const Request::FGetSeasonGatheringRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FSeasonGatheringDomain>& Self,
                const Request::FGetSeasonGatheringRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetSeasonGatheringRequestPtr Request
        );

        class GS2MATCHMAKING_API FVerifyIncludeParticipantTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain>,
            public TSharedFromThis<FVerifyIncludeParticipantTask>
        {
            const TSharedPtr<FSeasonGatheringDomain> Self;
            const Request::FVerifyIncludeParticipantByUserIdRequestPtr Request;
        public:
            explicit FVerifyIncludeParticipantTask(
                const TSharedPtr<FSeasonGatheringDomain>& Self,
                const Request::FVerifyIncludeParticipantByUserIdRequestPtr Request
            );

            FVerifyIncludeParticipantTask(
                const FVerifyIncludeParticipantTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain>> Result
            ) override;
        };
        friend FVerifyIncludeParticipantTask;

        TSharedPtr<FAsyncTask<FVerifyIncludeParticipantTask>> VerifyIncludeParticipant(
            Request::FVerifyIncludeParticipantByUserIdRequestPtr Request
        );

        class GS2MATCHMAKING_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FSeasonGatheringDomain> Self;
            const Request::FDeleteSeasonGatheringRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FSeasonGatheringDomain>& Self,
                const Request::FDeleteSeasonGatheringRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteSeasonGatheringRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> SeasonName,
            TOptional<FString> Season,
            TOptional<FString> Tier,
            TOptional<FString> SeasonGatheringName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> Tier,
            TOptional<FString> SeasonGatheringName
        );

        class GS2MATCHMAKING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FSeasonGathering>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSeasonGatheringDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSeasonGatheringDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Matchmaking::Model::FSeasonGatheringPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FSeasonGatheringDomain> FSeasonGatheringDomainPtr;
}
