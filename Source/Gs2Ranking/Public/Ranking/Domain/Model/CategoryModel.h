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
    class FRankingCategoryDomain;
    class FRankingCategoryAccessTokenDomain;
    class FSubscribeUserDomain;
    class FSubscribeUserAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2RANKING_API FCategoryModelDomain:
        public TSharedFromThis<FCategoryModelDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Ranking::Domain::FGs2RankingDomainPtr Service;
        const Gs2::Ranking::FGs2RankingRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> CategoryName;
    private:

        FString ParentKey;

    public:

        FCategoryModelDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Ranking::Domain::FGs2RankingDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> CategoryName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCategoryModelDomain(
            const FCategoryModelDomain& From
        );

        class GS2RANKING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking::Model::FCategoryModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCategoryModelDomain> Self;
            const Request::FGetCategoryModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCategoryModelDomain>& Self,
                const Request::FGetCategoryModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FCategoryModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCategoryModelRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> CategoryName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> CategoryName
        );

        class GS2RANKING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking::Model::FCategoryModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCategoryModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCategoryModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FCategoryModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Ranking::Model::FCategoryModelPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCategoryModelDomain> FCategoryModelDomainPtr;
}
