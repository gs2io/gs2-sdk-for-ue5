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

    class GS2MATCHMAKING_API FRatingModelMasterDomain:
        public TSharedFromThis<FRatingModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> RatingName;
    private:

        FString ParentKey;

    public:

        FRatingModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> RatingName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRatingModelMasterDomain(
            const FRatingModelMasterDomain& From
        );

        class GS2MATCHMAKING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FRatingModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRatingModelMasterDomain> Self;
            const Request::FGetRatingModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRatingModelMasterDomain> Self,
                const Request::FGetRatingModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FRatingModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetRatingModelMasterRequestPtr Request
        );

        class GS2MATCHMAKING_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FRatingModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FRatingModelMasterDomain> Self;
            const Request::FUpdateRatingModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FRatingModelMasterDomain> Self,
                const Request::FUpdateRatingModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateRatingModelMasterRequestPtr Request
        );

        class GS2MATCHMAKING_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FRatingModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FRatingModelMasterDomain> Self;
            const Request::FDeleteRatingModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FRatingModelMasterDomain> Self,
                const Request::FDeleteRatingModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FRatingModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteRatingModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> RatingName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> RatingName
        );

        class GS2MATCHMAKING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FRatingModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FRatingModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRatingModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FRatingModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FRatingModelMasterDomain> FRatingModelMasterDomainPtr;
}
