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

    class GS2RANKING_API FScoreDomain:
        public TSharedFromThis<FScoreDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Ranking::FGs2RankingRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> CategoryName;
        TOptional<FString> ScorerUserId;
        TOptional<FString> UniqueId;
    private:

        FString ParentKey;

    public:

        FScoreDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> CategoryName,
            const TOptional<FString> ScorerUserId,
            const TOptional<FString> UniqueId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FScoreDomain(
            const FScoreDomain& From
        );

        class GS2RANKING_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking::Model::FScore>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FScoreDomain> Self;
            const Request::FGetScoreByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FScoreDomain> Self,
                const Request::FGetScoreByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FScore>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetScoreByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> CategoryName,
            TOptional<FString> ScorerUserId,
            TOptional<FString> UniqueId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> CategoryName,
            TOptional<FString> ScorerUserId,
            TOptional<FString> UniqueId
        );

        class GS2RANKING_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking::Model::FScore>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FScoreDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FScoreDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FScore>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FScoreDomain> FScoreDomainPtr;
}
