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

    class GS2RANKING2_API FSubscribeRankingDataAccessTokenDomain:
        public TSharedFromThis<FSubscribeRankingDataAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Ranking2::Domain::FGs2Ranking2DomainPtr Service;
        const Gs2::Ranking2::FGs2Ranking2RestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> RankingName;
        TOptional<int64> Season;
        TOptional<FString> ScorerUserId;
    private:

        FString ParentKey;

    public:

        FSubscribeRankingDataAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> RankingName,
            const TOptional<int64> Season,
            const TOptional<FString> ScorerUserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSubscribeRankingDataAccessTokenDomain(
            const FSubscribeRankingDataAccessTokenDomain& From
        );

        class GS2RANKING2_API FGetSubscribeRankingTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FSubscribeRankingDataAccessTokenDomain>,
            public TSharedFromThis<FGetSubscribeRankingTask>
        {
            const TSharedPtr<FSubscribeRankingDataAccessTokenDomain> Self;
            const Request::FGetSubscribeRankingRequestPtr Request;
        public:
            explicit FGetSubscribeRankingTask(
                const TSharedPtr<FSubscribeRankingDataAccessTokenDomain>& Self,
                const Request::FGetSubscribeRankingRequestPtr Request
            );

            FGetSubscribeRankingTask(
                const FGetSubscribeRankingTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingDataAccessTokenDomain>> Result
            ) override;
        };
        friend FGetSubscribeRankingTask;

        TSharedPtr<FAsyncTask<FGetSubscribeRankingTask>> GetSubscribeRanking(
            Request::FGetSubscribeRankingRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> RankingName,
            TOptional<FString> Season,
            TOptional<FString> ScorerUserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ScorerUserId
        );

        class GS2RANKING2_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Model::FSubscribeRankingData>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSubscribeRankingDataAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSubscribeRankingDataAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FSubscribeRankingData>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Ranking2::Model::FSubscribeRankingDataPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FSubscribeRankingDataAccessTokenDomain> FSubscribeRankingDataAccessTokenDomainPtr;
}
