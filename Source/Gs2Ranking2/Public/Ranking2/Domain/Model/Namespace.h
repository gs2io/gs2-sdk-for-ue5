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

    class GS2RANKING2_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Ranking2::Domain::FGs2Ranking2DomainPtr Service;
        const Gs2::Ranking2::FGs2Ranking2RestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> Url;
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2RANKING2_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2RANKING2_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2RANKING2_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2RANKING2_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2RANKING2_API FCreateGlobalRankingModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FGlobalRankingModelMasterDomain>,
            public TSharedFromThis<FCreateGlobalRankingModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateGlobalRankingModelMasterRequestPtr Request;
        public:
            explicit FCreateGlobalRankingModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateGlobalRankingModelMasterRequestPtr Request
            );

            FCreateGlobalRankingModelMasterTask(
                const FCreateGlobalRankingModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingModelMasterDomain>> Result
            ) override;
        };
        friend FCreateGlobalRankingModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateGlobalRankingModelMasterTask>> CreateGlobalRankingModelMaster(
            Request::FCreateGlobalRankingModelMasterRequestPtr Request
        );

        class GS2RANKING2_API FCreateSubscribeRankingModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain>,
            public TSharedFromThis<FCreateSubscribeRankingModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateSubscribeRankingModelMasterRequestPtr Request;
        public:
            explicit FCreateSubscribeRankingModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateSubscribeRankingModelMasterRequestPtr Request
            );

            FCreateSubscribeRankingModelMasterTask(
                const FCreateSubscribeRankingModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain>> Result
            ) override;
        };
        friend FCreateSubscribeRankingModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateSubscribeRankingModelMasterTask>> CreateSubscribeRankingModelMaster(
            Request::FCreateSubscribeRankingModelMasterRequestPtr Request
        );

        class GS2RANKING2_API FCreateClusterRankingModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Domain::Model::FClusterRankingModelMasterDomain>,
            public TSharedFromThis<FCreateClusterRankingModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateClusterRankingModelMasterRequestPtr Request;
        public:
            explicit FCreateClusterRankingModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateClusterRankingModelMasterRequestPtr Request
            );

            FCreateClusterRankingModelMasterTask(
                const FCreateClusterRankingModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingModelMasterDomain>> Result
            ) override;
        };
        friend FCreateClusterRankingModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateClusterRankingModelMasterTask>> CreateClusterRankingModelMaster(
            Request::FCreateClusterRankingModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FCurrentRankingMasterDomain> CurrentRankingMaster(
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingModelsIteratorPtr GlobalRankingModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankingModels(
            TFunction<void()> Callback
        );

        void UnsubscribeGlobalRankingModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingModelDomain> GlobalRankingModel(
            const FString RankingName
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeGlobalRankingModelMastersIteratorPtr GlobalRankingModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankingModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeGlobalRankingModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingModelMasterDomain> GlobalRankingModelMaster(
            const FString RankingName
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeSubscribeRankingModelsIteratorPtr SubscribeRankingModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscribeRankingModels(
            TFunction<void()> Callback
        );

        void UnsubscribeSubscribeRankingModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingModelDomain> SubscribeRankingModel(
            const FString RankingName
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeSubscribeRankingModelMastersIteratorPtr SubscribeRankingModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscribeRankingModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeSubscribeRankingModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FSubscribeRankingModelMasterDomain> SubscribeRankingModelMaster(
            const FString RankingName
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingModelsIteratorPtr ClusterRankingModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeClusterRankingModels(
            TFunction<void()> Callback
        );

        void UnsubscribeClusterRankingModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingModelDomain> ClusterRankingModel(
            const FString RankingName
        );

        Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingModelMastersIteratorPtr ClusterRankingModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeClusterRankingModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeClusterRankingModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingModelMasterDomain> ClusterRankingModelMaster(
            const FString RankingName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2RANKING2_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking2::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Ranking2::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
