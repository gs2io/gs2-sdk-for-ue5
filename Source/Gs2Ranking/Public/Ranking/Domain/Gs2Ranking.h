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

#include "Core/Gs2Core.h"
#include "Core/Domain/Gs2Core.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Ranking/Gs2Ranking.h"

// Model
#include "Ranking/Domain/Model/Namespace.h"
#include "Ranking/Domain/Model/CategoryModel.h"
#include "Ranking/Domain/Model/CategoryModelMaster.h"
#include "Ranking/Domain/Model/Score.h"
#include "Ranking/Domain/Model/ScoreAccessToken.h"
#include "Ranking/Domain/Model/Ranking.h"
#include "Ranking/Domain/Model/RankingAccessToken.h"
#include "Ranking/Domain/Model/CurrentRankingMaster.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking/Domain/Model/User.h"
#include "Ranking/Domain/Model/UserAccessToken.h"

// Iterator
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

// Notification

namespace Gs2::Ranking::Domain
{

    class GS2RANKING_API FGs2RankingDomain:
        public TSharedFromThis<FGs2RankingDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Ranking::FGs2RankingRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2RankingDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2RankingDomain(
            const FGs2RankingDomain& From
        );

        class GS2RANKING_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2RankingDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2RankingDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Ranking::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        TSharedPtr<Gs2::Ranking::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        ) const;

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );

        void HandleNotification(
            const FString Action,
            const FString Payload
        );
    };
    typedef TSharedPtr<FGs2RankingDomain> FGs2RankingDomainPtr;
}
