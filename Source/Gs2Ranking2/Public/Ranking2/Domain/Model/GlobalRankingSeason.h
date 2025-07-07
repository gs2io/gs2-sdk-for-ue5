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
#include "Ranking2/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Ranking2/Domain/Iterator/DescribeGlobalRankingModelsIterator.h"
#include "Ranking2/Domain/Iterator/DescribeGlobalRankingModelMastersIterator.h"
#include "Ranking2/Domain/Iterator/DescribeGlobalRankingScoresIterator.h"
#include "Ranking2/Domain/Iterator/DescribeGlobalRankingScoresByUserIdIterator.h"
#include "Ranking2/Domain/Iterator/DescribeGlobalRankingReceivedRewardsIterator.h"
#include "Ranking2/Domain/Iterator/DescribeGlobalRankingReceivedRewardsByUserIdIterator.h"
#include "Ranking2/Domain/Iterator/DescribeGlobalRankingsIterator.h"
#include "Ranking2/Domain/Iterator/DescribeGlobalRankingsByUserIdIterator.h"
#include "Ranking2/Domain/Iterator/DescribeClusterRankingModelsIterator.h"
#include "Ranking2/Domain/Iterator/DescribeClusterRankingModelMastersIterator.h"
#include "Ranking2/Domain/Iterator/DescribeClusterRankingScoresIterator.h"
#include "Ranking2/Domain/Iterator/DescribeClusterRankingScoresByUserIdIterator.h"
#include "Ranking2/Domain/Iterator/DescribeClusterRankingReceivedRewardsIterator.h"
#include "Ranking2/Domain/Iterator/DescribeClusterRankingReceivedRewardsByUserIdIterator.h"
#include "Ranking2/Domain/Iterator/DescribeClusterRankingsIterator.h"
#include "Ranking2/Domain/Iterator/DescribeClusterRankingsByUserIdIterator.h"
#include "Ranking2/Domain/Iterator/DescribeSubscribeRankingModelsIterator.h"
#include "Ranking2/Domain/Iterator/DescribeSubscribeRankingModelMastersIterator.h"
#include "Ranking2/Domain/Iterator/DescribeSubscribesIterator.h"
#include "Ranking2/Domain/Iterator/DescribeSubscribesByUserIdIterator.h"
#include "Ranking2/Domain/Iterator/DescribeSubscribeRankingScoresIterator.h"
#include "Ranking2/Domain/Iterator/DescribeSubscribeRankingScoresByUserIdIterator.h"
#include "Ranking2/Domain/Iterator/DescribeSubscribeRankingsIterator.h"
#include "Ranking2/Domain/Iterator/DescribeSubscribeRankingsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Ranking2::Domain
{
    class FGs2Ranking2Domain;
    typedef TSharedPtr<FGs2Ranking2Domain> FGs2Ranking2DomainPtr;
}

namespace Gs2::Ranking2::Domain::Model
{
    class FNamespaceDomain;
    class FGlobalRankingModelDomain;
    class FGlobalRankingModelMasterDomain;
    class FGlobalRankingScoreDomain;
    class FGlobalRankingScoreAccessTokenDomain;
    class FGlobalRankingReceivedRewardDomain;
    class FGlobalRankingReceivedRewardAccessTokenDomain;
    class FGlobalRankingSeasonDomain;
    class FGlobalRankingSeasonAccessTokenDomain;
    class FGlobalRankingDataDomain;
    class FGlobalRankingDataAccessTokenDomain;
    class FClusterRankingModelDomain;
    class FClusterRankingModelMasterDomain;
    class FClusterRankingScoreDomain;
    class FClusterRankingScoreAccessTokenDomain;
    class FClusterRankingReceivedRewardDomain;
    class FClusterRankingReceivedRewardAccessTokenDomain;
    class FClusterRankingSeasonDomain;
    class FClusterRankingSeasonAccessTokenDomain;
    class FClusterRankingDataDomain;
    class FClusterRankingDataAccessTokenDomain;
    class FSubscribeRankingModelDomain;
    class FSubscribeRankingModelMasterDomain;
    class FSubscribeRankingSeasonDomain;
    class FSubscribeRankingSeasonAccessTokenDomain;
    class FSubscribeDomain;
    class FSubscribeAccessTokenDomain;
    class FSubscribeRankingScoreDomain;
    class FSubscribeRankingScoreAccessTokenDomain;
    class FSubscribeRankingDataDomain;
    class FSubscribeRankingDataAccessTokenDomain;
    class FCurrentRankingMasterDomain;
    class FSubscribeUserDomain;
    class FSubscribeUserAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2RANKING2_API FGlobalRankingSeasonDomain:
        public TSharedFromThis<FGlobalRankingSeasonDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Ranking2::Domain::FGs2Ranking2DomainPtr Service;
        const Gs2::Ranking2::FGs2Ranking2RestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> RankingName;
        TOptional<int64> Season;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FGlobalRankingSeasonDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> RankingName,
            const TOptional<int64> Season,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGlobalRankingSeasonDomain(
            const FGlobalRankingSeasonDomain& From
        );

        class GS2RANKING2_API FPutGlobalRankingScoreTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain>,
            public TSharedFromThis<FPutGlobalRankingScoreTask>
        {
            const TSharedPtr<FGlobalRankingSeasonDomain> Self;
            const Request::FPutGlobalRankingScoreByUserIdRequestPtr Request;
        public:
            explicit FPutGlobalRankingScoreTask(
                const TSharedPtr<FGlobalRankingSeasonDomain>& Self,
                const Request::FPutGlobalRankingScoreByUserIdRequestPtr Request
            );

            FPutGlobalRankingScoreTask(
                const FPutGlobalRankingScoreTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain>> Result
            ) override;
        };
        friend FPutGlobalRankingScoreTask;

        TSharedPtr<FAsyncTask<FPutGlobalRankingScoreTask>> PutGlobalRankingScore(
            Request::FPutGlobalRankingScoreByUserIdRequestPtr Request
        );

        class GS2RANKING2_API FGetGlobalRankingTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FGlobalRankingDataDomain>,
            public TSharedFromThis<FGetGlobalRankingTask>
        {
            const TSharedPtr<FGlobalRankingSeasonDomain> Self;
            const Request::FGetGlobalRankingByUserIdRequestPtr Request;
        public:
            explicit FGetGlobalRankingTask(
                const TSharedPtr<FGlobalRankingSeasonDomain>& Self,
                const Request::FGetGlobalRankingByUserIdRequestPtr Request
            );

            FGetGlobalRankingTask(
                const FGetGlobalRankingTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingDataDomain>> Result
            ) override;
        };
        friend FGetGlobalRankingTask;

        TSharedPtr<FAsyncTask<FGetGlobalRankingTask>> GetGlobalRanking(
            Request::FGetGlobalRankingByUserIdRequestPtr Request
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingScoresByUserIdIteratorPtr GlobalRankingScores(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankingScores(
            TFunction<void()> Callback
        );

        void UnsubscribeGlobalRankingScores(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain> GlobalRankingScore(
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingsByUserIdIteratorPtr GlobalRankings(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankings(
            TFunction<void()> Callback
        );

        void UnsubscribeGlobalRankings(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingDataDomain> GlobalRankingData(
            const FString ScorerUserId
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingReceivedRewardsByUserIdIteratorPtr GlobalRankingReceivedRewards(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankingReceivedRewards(
            TFunction<void()> Callback
        );

        void UnsubscribeGlobalRankingReceivedRewards(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardDomain> GlobalRankingReceivedReward(
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> RankingName,
            TOptional<int64> Season,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<int64> Season
        );

    };

    typedef TSharedPtr<FGlobalRankingSeasonDomain> FGlobalRankingSeasonDomainPtr;
}
