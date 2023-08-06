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
#include "Showcase/Domain/Iterator/DescribeRandomShowcaseMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomDisplayItemsIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomDisplayItemsByUserIdIterator.h"

namespace Gs2::Showcase::Domain::Model
{
    class FNamespaceDomain;
    class FSalesItemMasterDomain;
    class FSalesItemGroupMasterDomain;
    class FShowcaseMasterDomain;
    class FCurrentShowcaseMasterDomain;
    class FShowcaseDomain;
    class FShowcaseAccessTokenDomain;
    class FDisplayItemDomain;
    class FDisplayItemAccessTokenDomain;
    class FRandomShowcaseMasterDomain;
    class FRandomShowcaseDomain;
    class FRandomShowcaseAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FRandomShowcaseStatusDomain;
    class FRandomShowcaseStatusAccessTokenDomain;
    class FRandomDisplayItemDomain;
    class FRandomDisplayItemAccessTokenDomain;

    class GS2SHOWCASE_API FRandomShowcaseMasterDomain:
        public TSharedFromThis<FRandomShowcaseMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> ShowcaseName;
    private:

        FString ParentKey;

    public:

        FRandomShowcaseMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> ShowcaseName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRandomShowcaseMasterDomain(
            const FRandomShowcaseMasterDomain& From
        );

        class GS2SHOWCASE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FRandomShowcaseMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRandomShowcaseMasterDomain> Self;
            const Request::FGetRandomShowcaseMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRandomShowcaseMasterDomain> Self,
                const Request::FGetRandomShowcaseMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomShowcaseMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetRandomShowcaseMasterRequestPtr Request
        );

        class GS2SHOWCASE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FRandomShowcaseMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FRandomShowcaseMasterDomain> Self;
            const Request::FUpdateRandomShowcaseMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FRandomShowcaseMasterDomain> Self,
                const Request::FUpdateRandomShowcaseMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomShowcaseMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateRandomShowcaseMasterRequestPtr Request
        );

        class GS2SHOWCASE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FRandomShowcaseMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FRandomShowcaseMasterDomain> Self;
            const Request::FDeleteRandomShowcaseMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FRandomShowcaseMasterDomain> Self,
                const Request::FDeleteRandomShowcaseMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomShowcaseMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteRandomShowcaseMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> ShowcaseName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ShowcaseName
        );

        class GS2SHOWCASE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FRandomShowcaseMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FRandomShowcaseMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRandomShowcaseMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomShowcaseMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FRandomShowcaseMasterDomain> FRandomShowcaseMasterDomainPtr;
}
