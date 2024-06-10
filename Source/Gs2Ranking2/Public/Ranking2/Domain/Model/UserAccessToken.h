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
 *
 * deny overwrite
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Ranking2/Gs2Ranking2.h"
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
    class FGlobalRankingDataDomain;
    class FGlobalRankingDataAccessTokenDomain;
    class FClusterRankingModelDomain;
    class FClusterRankingModelMasterDomain;
    class FClusterRankingScoreDomain;
    class FClusterRankingScoreAccessTokenDomain;
    class FClusterRankingReceivedRewardDomain;
    class FClusterRankingReceivedRewardAccessTokenDomain;
    class FClusterRankingSeasonDomain;
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

    class GS2RANKING2_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
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
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2RANKING2_API FPutGlobalRankingScoreTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain>,
            public TSharedFromThis<FPutGlobalRankingScoreTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FPutGlobalRankingScoreRequestPtr Request;
        public:
            explicit FPutGlobalRankingScoreTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FPutGlobalRankingScoreRequestPtr Request
            );

            FPutGlobalRankingScoreTask(
                const FPutGlobalRankingScoreTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain>> Result
            ) override;
        };
        friend FPutGlobalRankingScoreTask;

        TSharedPtr<FAsyncTask<FPutGlobalRankingScoreTask>> PutGlobalRankingScore(
            Request::FPutGlobalRankingScoreRequestPtr Request
        );

        class GS2RANKING2_API FPutClusterRankingScoreTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain>,
            public TSharedFromThis<FPutClusterRankingScoreTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FPutClusterRankingScoreRequestPtr Request;
        public:
            explicit FPutClusterRankingScoreTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FPutClusterRankingScoreRequestPtr Request
            );

            FPutClusterRankingScoreTask(
                const FPutClusterRankingScoreTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain>> Result
            ) override;
        };
        friend FPutClusterRankingScoreTask;

        TSharedPtr<FAsyncTask<FPutClusterRankingScoreTask>> PutClusterRankingScore(
            Request::FPutClusterRankingScoreRequestPtr Request
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingScoresIteratorPtr GlobalRankingScores(
            const TOptional<FString> RankingName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankingScores(
            TFunction<void()> Callback
        );

        void UnsubscribeGlobalRankingScores(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain> GlobalRankingScore(
            const FString RankingName,
            const TOptional<int64> Season = TOptional<int64>()
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonAccessTokenDomain> SubscribeRankingSeason(
            const FString RankingName,
            const TOptional<int64> Season = TOptional<int64>()
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeSubscribesIteratorPtr Subscribes(
            const TOptional<FString> RankingName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscribes(
            const TOptional<FString> RankingName,
            TFunction<void()> Callback
        );

        void UnsubscribeSubscribes(
            const TOptional<FString> RankingName,
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeAccessTokenDomain> Subscribe(
            const FString RankingName
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingReceivedRewardsIteratorPtr GlobalRankingReceivedRewards(
            const TOptional<FString> RankingName = TOptional<FString>(),
            const TOptional<int64> Season = TOptional<int64>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankingReceivedRewards(
            TFunction<void()> Callback
        );

        void UnsubscribeGlobalRankingReceivedRewards(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardAccessTokenDomain> GlobalRankingReceivedReward(
            const FString RankingName,
            const TOptional<int64> Season = TOptional<int64>()
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsIteratorPtr ClusterRankingReceivedRewards(
            const TOptional<FString> RankingName = TOptional<FString>(),
            const TOptional<FString> ClusterName = TOptional<FString>(),
            const TOptional<int64> Season = TOptional<int64>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeClusterRankingReceivedRewards(
            TFunction<void()> Callback
        );

        void UnsubscribeClusterRankingReceivedRewards(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardAccessTokenDomain> ClusterRankingReceivedReward(
            const FString RankingName,
            const FString ClusterName,
            const TOptional<int64> Season = TOptional<int64>()
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingScoresIteratorPtr ClusterRankingScores(
            const TOptional<FString> RankingName = TOptional<FString>(),
            const TOptional<FString> ClusterName = TOptional<FString>(),
            const TOptional<int64> Season = TOptional<int64>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeClusterRankingScores(
            TFunction<void()> Callback
        );

        void UnsubscribeClusterRankingScores(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingScoreAccessTokenDomain> ClusterRankingScore(
            const FString RankingName,
            const FString ClusterName,
            const TOptional<int64> Season = TOptional<int64>()
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
