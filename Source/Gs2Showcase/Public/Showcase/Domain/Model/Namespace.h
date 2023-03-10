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
#include "Showcase/Gs2Showcase.h"
#include "Showcase/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Showcase/Domain/Iterator/DescribeSalesItemMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeSalesItemGroupMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcaseMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcasesIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcasesByUserIdIterator.h"

namespace Gs2::Showcase::Domain::Model
{
    class FNamespaceDomain;
    class FSalesItemMasterDomain;
    class FSalesItemGroupMasterDomain;
    class FShowcaseMasterDomain;
    class FCurrentShowcaseMasterDomain;
    class FShowcaseDomain;
    class FShowcaseAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2SHOWCASE_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

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

        class GS2SHOWCASE_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2SHOWCASE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2SHOWCASE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2SHOWCASE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FNamespaceDomain>,
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
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2SHOWCASE_API FCreateSalesItemMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain>,
            public TSharedFromThis<FCreateSalesItemMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateSalesItemMasterRequestPtr Request;
        public:
            explicit FCreateSalesItemMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateSalesItemMasterRequestPtr Request
            );

            FCreateSalesItemMasterTask(
                const FCreateSalesItemMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain>> Result
            ) override;
        };
        friend FCreateSalesItemMasterTask;

        TSharedPtr<FAsyncTask<FCreateSalesItemMasterTask>> CreateSalesItemMaster(
            Request::FCreateSalesItemMasterRequestPtr Request
        );

        class GS2SHOWCASE_API FCreateSalesItemGroupMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain>,
            public TSharedFromThis<FCreateSalesItemGroupMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateSalesItemGroupMasterRequestPtr Request;
        public:
            explicit FCreateSalesItemGroupMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateSalesItemGroupMasterRequestPtr Request
            );

            FCreateSalesItemGroupMasterTask(
                const FCreateSalesItemGroupMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain>> Result
            ) override;
        };
        friend FCreateSalesItemGroupMasterTask;

        TSharedPtr<FAsyncTask<FCreateSalesItemGroupMasterTask>> CreateSalesItemGroupMaster(
            Request::FCreateSalesItemGroupMasterRequestPtr Request
        );

        class GS2SHOWCASE_API FCreateShowcaseMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FShowcaseMasterDomain>,
            public TSharedFromThis<FCreateShowcaseMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateShowcaseMasterRequestPtr Request;
        public:
            explicit FCreateShowcaseMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateShowcaseMasterRequestPtr Request
            );

            FCreateShowcaseMasterTask(
                const FCreateShowcaseMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FShowcaseMasterDomain>> Result
            ) override;
        };
        friend FCreateShowcaseMasterTask;

        TSharedPtr<FAsyncTask<FCreateShowcaseMasterTask>> CreateShowcaseMaster(
            Request::FCreateShowcaseMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Showcase::Domain::Model::FCurrentShowcaseMasterDomain> CurrentShowcaseMaster(
        ) const;

        TSharedPtr<Gs2::Showcase::Domain::Model::FUserDomain> User(
            const FString UserId
        ) const;

        TSharedPtr<Gs2::Showcase::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        ) const;

        Gs2::Showcase::Domain::Iterator::FDescribeSalesItemMastersIteratorPtr SalesItemMasters(
        ) const;

        TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain> SalesItemMaster(
            const FString SalesItemName
        ) const;

        Gs2::Showcase::Domain::Iterator::FDescribeSalesItemGroupMastersIteratorPtr SalesItemGroupMasters(
        ) const;

        TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemGroupMasterDomain> SalesItemGroupMaster(
            const FString SalesItemGroupName
        ) const;

        Gs2::Showcase::Domain::Iterator::FDescribeShowcaseMastersIteratorPtr ShowcaseMasters(
        ) const;

        TSharedPtr<Gs2::Showcase::Domain::Model::FShowcaseMasterDomain> ShowcaseMaster(
            const FString ShowcaseName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2SHOWCASE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
