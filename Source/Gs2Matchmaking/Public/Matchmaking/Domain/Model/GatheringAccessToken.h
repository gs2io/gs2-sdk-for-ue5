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
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FRatingDomain;
    class FRatingAccessTokenDomain;
    class FBallotDomain;
    class FBallotAccessTokenDomain;
    class FVoteDomain;

    class GS2MATCHMAKING_API FGatheringAccessTokenDomain:
        public TSharedFromThis<FGatheringAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Matchmaking::Domain::FGs2MatchmakingDomainPtr Service;
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> GatheringName;
    private:

        FString ParentKey;

    public:

        FGatheringAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Matchmaking::Domain::FGs2MatchmakingDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> GatheringName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGatheringAccessTokenDomain(
            const FGatheringAccessTokenDomain& From
        );

        class GS2MATCHMAKING_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FGatheringAccessTokenDomain> Self;
            const Request::FUpdateGatheringRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FGatheringAccessTokenDomain>& Self,
                const Request::FUpdateGatheringRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateGatheringRequestPtr Request
        );

        class GS2MATCHMAKING_API FPingTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>,
            public TSharedFromThis<FPingTask>
        {
            const TSharedPtr<FGatheringAccessTokenDomain> Self;
            const Request::FPingRequestPtr Request;
        public:
            explicit FPingTask(
                const TSharedPtr<FGatheringAccessTokenDomain>& Self,
                const Request::FPingRequestPtr Request
            );

            FPingTask(
                const FPingTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>> Result
            ) override;
        };
        friend FPingTask;

        TSharedPtr<FAsyncTask<FPingTask>> Ping(
            Request::FPingRequestPtr Request
        );

        class GS2MATCHMAKING_API FCancelMatchmakingTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>,
            public TSharedFromThis<FCancelMatchmakingTask>
        {
            const TSharedPtr<FGatheringAccessTokenDomain> Self;
            const Request::FCancelMatchmakingRequestPtr Request;
        public:
            explicit FCancelMatchmakingTask(
                const TSharedPtr<FGatheringAccessTokenDomain>& Self,
                const Request::FCancelMatchmakingRequestPtr Request
            );

            FCancelMatchmakingTask(
                const FCancelMatchmakingTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>> Result
            ) override;
        };
        friend FCancelMatchmakingTask;

        TSharedPtr<FAsyncTask<FCancelMatchmakingTask>> CancelMatchmaking(
            Request::FCancelMatchmakingRequestPtr Request
        );

        class GS2MATCHMAKING_API FEarlyCompleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>,
            public TSharedFromThis<FEarlyCompleteTask>
        {
            const TSharedPtr<FGatheringAccessTokenDomain> Self;
            const Request::FEarlyCompleteRequestPtr Request;
        public:
            explicit FEarlyCompleteTask(
                const TSharedPtr<FGatheringAccessTokenDomain>& Self,
                const Request::FEarlyCompleteRequestPtr Request
            );

            FEarlyCompleteTask(
                const FEarlyCompleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FGatheringAccessTokenDomain>> Result
            ) override;
        };
        friend FEarlyCompleteTask;

        TSharedPtr<FAsyncTask<FEarlyCompleteTask>> EarlyComplete(
            Request::FEarlyCompleteRequestPtr Request
        );

        class GS2MATCHMAKING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FGathering>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FGatheringAccessTokenDomain> Self;
            const Request::FGetGatheringRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FGatheringAccessTokenDomain>& Self,
                const Request::FGetGatheringRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FGathering>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetGatheringRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> GatheringName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> GatheringName
        );

        class GS2MATCHMAKING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FGathering>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FGatheringAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FGatheringAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FGathering>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Matchmaking::Model::FGatheringPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FGatheringAccessTokenDomain> FGatheringAccessTokenDomainPtr;
}
