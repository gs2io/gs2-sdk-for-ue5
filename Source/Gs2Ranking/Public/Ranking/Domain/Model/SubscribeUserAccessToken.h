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

namespace Gs2::Ranking::Domain
{
    class FGs2RankingDomain;
    typedef TSharedPtr<FGs2RankingDomain> FGs2RankingDomainPtr;
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

    class GS2RANKING_API FSubscribeUserAccessTokenDomain:
        public TSharedFromThis<FSubscribeUserAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Ranking::Domain::FGs2RankingDomainPtr Service;
        const Gs2::Ranking::FGs2RankingRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> CategoryName;
        TOptional<FString> TargetUserId;
    private:

        FString ParentKey;

    public:

        FSubscribeUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Ranking::Domain::FGs2RankingDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> CategoryName,
            const TOptional<FString> TargetUserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSubscribeUserAccessTokenDomain(
            const FSubscribeUserAccessTokenDomain& From
        );

        class GS2RANKING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking::Model::FSubscribeUser>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FSubscribeUserAccessTokenDomain> Self;
            const Request::FGetSubscribeRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FSubscribeUserAccessTokenDomain>& Self,
                const Request::FGetSubscribeRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FSubscribeUser>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetSubscribeRequestPtr Request
        );

        class GS2RANKING_API FUnsubscribeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain>,
            public TSharedFromThis<FUnsubscribeTask>
        {
            const TSharedPtr<FSubscribeUserAccessTokenDomain> Self;
            const Request::FUnsubscribeRequestPtr Request;
        public:
            explicit FUnsubscribeTask(
                const TSharedPtr<FSubscribeUserAccessTokenDomain>& Self,
                const Request::FUnsubscribeRequestPtr Request
            );

            FUnsubscribeTask(
                const FUnsubscribeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserAccessTokenDomain>> Result
            ) override;
        };
        friend FUnsubscribeTask;

        TSharedPtr<FAsyncTask<FUnsubscribeTask>> Unsubscribe(
            Request::FUnsubscribeRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> CategoryName,
            TOptional<FString> TargetUserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> CategoryName,
            TOptional<FString> TargetUserId
        );

        class GS2RANKING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking::Model::FSubscribeUser>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSubscribeUserAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSubscribeUserAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FSubscribeUser>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Ranking::Model::FSubscribeUserPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FSubscribeUserAccessTokenDomain> FSubscribeUserAccessTokenDomainPtr;
}
