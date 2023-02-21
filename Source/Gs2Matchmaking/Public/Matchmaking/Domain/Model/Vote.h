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

    class GS2MATCHMAKING_API FVoteDomain:
        public TSharedFromThis<FVoteDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> RatingName;
        TOptional<FString> GatheringName;
    private:

        FString ParentKey;

    public:

        FVoteDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> RatingName,
            const TOptional<FString> GatheringName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FVoteDomain(
            const FVoteDomain& From
        );

        class GS2MATCHMAKING_API FCommitTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Domain::Model::FVoteDomain>,
            public TSharedFromThis<FCommitTask>
        {
            const TSharedPtr<FVoteDomain> Self;
            const Request::FCommitVoteRequestPtr Request;
        public:
            explicit FCommitTask(
                const TSharedPtr<FVoteDomain> Self,
                const Request::FCommitVoteRequestPtr Request
            );

            FCommitTask(
                const FCommitTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FVoteDomain>> Result
            ) override;
        };
        friend FCommitTask;

        TSharedPtr<FAsyncTask<FCommitTask>> Commit(
            Request::FCommitVoteRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> RatingName,
            TOptional<FString> GatheringName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> RatingName,
            TOptional<FString> GatheringName
        );

        class GS2MATCHMAKING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Matchmaking::Model::FVote>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FVoteDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FVoteDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FVote>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FVoteDomain> FVoteDomainPtr;
}
