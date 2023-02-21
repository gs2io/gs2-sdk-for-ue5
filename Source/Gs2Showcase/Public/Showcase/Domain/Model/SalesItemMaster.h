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

    class GS2SHOWCASE_API FSalesItemMasterDomain:
        public TSharedFromThis<FSalesItemMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> SalesItemName;
    private:

        FString ParentKey;

    public:

        FSalesItemMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> SalesItemName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSalesItemMasterDomain(
            const FSalesItemMasterDomain& From
        );

        class GS2SHOWCASE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FSalesItemMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FSalesItemMasterDomain> Self;
            const Request::FGetSalesItemMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FSalesItemMasterDomain> Self,
                const Request::FGetSalesItemMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FSalesItemMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetSalesItemMasterRequestPtr Request
        );

        class GS2SHOWCASE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FSalesItemMasterDomain> Self;
            const Request::FUpdateSalesItemMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FSalesItemMasterDomain> Self,
                const Request::FUpdateSalesItemMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateSalesItemMasterRequestPtr Request
        );

        class GS2SHOWCASE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FSalesItemMasterDomain> Self;
            const Request::FDeleteSalesItemMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FSalesItemMasterDomain> Self,
                const Request::FDeleteSalesItemMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FSalesItemMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteSalesItemMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> SalesItemName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> SalesItemName
        );

        class GS2SHOWCASE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FSalesItemMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSalesItemMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSalesItemMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FSalesItemMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FSalesItemMasterDomain> FSalesItemMasterDomainPtr;
}
