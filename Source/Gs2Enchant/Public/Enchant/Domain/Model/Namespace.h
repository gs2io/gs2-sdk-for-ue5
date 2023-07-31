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
#include "Enchant/Gs2Enchant.h"
#include "Enchant/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterModelsIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterModelMastersIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterModelsIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterModelMastersIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterStatusesIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterStatusesByUserIdIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterStatusesIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterStatusesByUserIdIterator.h"

namespace Gs2::Enchant::Domain::Model
{
    class FNamespaceDomain;
    class FBalanceParameterModelDomain;
    class FBalanceParameterModelMasterDomain;
    class FRarityParameterModelDomain;
    class FRarityParameterModelMasterDomain;
    class FCurrentParameterMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FBalanceParameterStatusDomain;
    class FBalanceParameterStatusAccessTokenDomain;
    class FRarityParameterStatusDomain;
    class FRarityParameterStatusAccessTokenDomain;

    class GS2ENCHANT_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Enchant::FGs2EnchantRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
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
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2ENCHANT_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2ENCHANT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2ENCHANT_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2ENCHANT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2ENCHANT_API FCreateBalanceParameterModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain>,
            public TSharedFromThis<FCreateBalanceParameterModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateBalanceParameterModelMasterRequestPtr Request;
        public:
            explicit FCreateBalanceParameterModelMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateBalanceParameterModelMasterRequestPtr Request
            );

            FCreateBalanceParameterModelMasterTask(
                const FCreateBalanceParameterModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain>> Result
            ) override;
        };
        friend FCreateBalanceParameterModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateBalanceParameterModelMasterTask>> CreateBalanceParameterModelMaster(
            Request::FCreateBalanceParameterModelMasterRequestPtr Request
        );

        class GS2ENCHANT_API FCreateRarityParameterModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain>,
            public TSharedFromThis<FCreateRarityParameterModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateRarityParameterModelMasterRequestPtr Request;
        public:
            explicit FCreateRarityParameterModelMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateRarityParameterModelMasterRequestPtr Request
            );

            FCreateRarityParameterModelMasterTask(
                const FCreateRarityParameterModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain>> Result
            ) override;
        };
        friend FCreateRarityParameterModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateRarityParameterModelMasterTask>> CreateRarityParameterModelMaster(
            Request::FCreateRarityParameterModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Enchant::Domain::Model::FCurrentParameterMasterDomain> CurrentParameterMaster(
        ) const;

        Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterModelsIteratorPtr BalanceParameterModels(
        ) const;

        TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterModelDomain> BalanceParameterModel(
            const FString ParameterName
        ) const;

        Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterModelMastersIteratorPtr BalanceParameterModelMasters(
        ) const;

        TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterModelMasterDomain> BalanceParameterModelMaster(
            const FString ParameterName
        ) const;

        Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterModelsIteratorPtr RarityParameterModels(
        ) const;

        TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterModelDomain> RarityParameterModel(
            const FString ParameterName
        ) const;

        Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterModelMastersIteratorPtr RarityParameterModelMasters(
        ) const;

        TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain> RarityParameterModelMaster(
            const FString ParameterName
        ) const;

        TSharedPtr<Gs2::Enchant::Domain::Model::FUserDomain> User(
            const FString UserId
        ) const;

        TSharedPtr<Gs2::Enchant::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2ENCHANT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}