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
#include "Ranking/Gs2Ranking.h"
#include "Ranking/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Ranking/Domain/Iterator/DescribeCategoryModelsIterator.h"
#include "Ranking/Domain/Iterator/DescribeCategoryModelMastersIterator.h"
#include "Ranking/Domain/Iterator/DescribeScoresIterator.h"
#include "Ranking/Domain/Iterator/DescribeScoresByUserIdIterator.h"
#include "Ranking/Domain/Iterator/DescribeRankingsIterator.h"
#include "Ranking/Domain/Iterator/DescribeRankingsByUserIdIterator.h"
#include "Ranking/Domain/Iterator/DescribeNearRankingsIterator.h"
#include "Ranking/Domain/Iterator/DescribeSubscribesByCategoryNameIterator.h"
#include "Ranking/Domain/Iterator/DescribeSubscribesByCategoryNameAndUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Ranking::Domain::Model
{
    class FNamespaceDomain;
    class FCategoryModelDomain;
    class FCategoryModelMasterDomain;
    class FSubscribeDomain;
    class FSubscribeAccessTokenDomain;
    class FScoreDomain;
    class FScoreAccessTokenDomain;
    class FRankingDomain;
    class FRankingAccessTokenDomain;
    class FCurrentRankingMasterDomain;
    class FSubscribeUserDomain;
    class FSubscribeUserAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2RANKING_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Ranking::FGs2RankingRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<bool> Processing;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<bool> GetProcessing() const
        {
            return Processing;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2RANKING_API FSubscribeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain>,
            public TSharedFromThis<FSubscribeTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FSubscribeRequestPtr Request;
        public:
            explicit FSubscribeTask(
                const TSharedPtr<FUserAccessTokenDomain> Self,
                const Request::FSubscribeRequestPtr Request
            );

            FSubscribeTask(
                const FSubscribeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain>> Result
            ) override;
        };
        friend FSubscribeTask;

        TSharedPtr<FAsyncTask<FSubscribeTask>> Subscribe(
            Request::FSubscribeRequestPtr Request
        );

        Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameIteratorPtr SubscribeUsers(
            const FString CategoryName
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscribeUsers(
            TFunction<void()> Callback
        );

        void UnsubscribeSubscribeUsers(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain> SubscribeUser(
            const FString CategoryName,
            const FString TargetUserId
        ) const;

        Gs2::Ranking::Domain::Iterator::FDescribeRankingsIteratorPtr Rankings(
            const FString CategoryName,
            const TOptional<FString> AdditionalScopeName = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRankings(
            TFunction<void()> Callback
        );

        void UnsubscribeRankings(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking::Domain::Model::FRankingAccessTokenDomain> Ranking(
            const FString CategoryName
        ) const;

        Gs2::Ranking::Domain::Iterator::FDescribeScoresIteratorPtr Scores(
            const FString CategoryName,
            const FString ScorerUserId
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeScores(
            TFunction<void()> Callback
        );

        void UnsubscribeScores(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking::Domain::Model::FScoreAccessTokenDomain> Score(
            const FString CategoryName,
            const FString ScorerUserId,
            const FString UniqueId
        ) const;

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
