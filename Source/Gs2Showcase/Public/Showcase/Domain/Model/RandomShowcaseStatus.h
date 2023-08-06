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

    class GS2SHOWCASE_API FRandomShowcaseStatusDomain:
        public TSharedFromThis<FRandomShowcaseStatusDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> ShowcaseName;
    private:

        FString ParentKey;

    public:

        FRandomShowcaseStatusDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> ShowcaseName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRandomShowcaseStatusDomain(
            const FRandomShowcaseStatusDomain& From
        );

        class GS2SHOWCASE_API FIncrementPurchaseCountTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>,
            public TSharedFromThis<FIncrementPurchaseCountTask>
        {
            const TSharedPtr<FRandomShowcaseStatusDomain> Self;
            const Request::FIncrementPurchaseCountByUserIdRequestPtr Request;
        public:
            explicit FIncrementPurchaseCountTask(
                const TSharedPtr<FRandomShowcaseStatusDomain> Self,
                const Request::FIncrementPurchaseCountByUserIdRequestPtr Request
            );

            FIncrementPurchaseCountTask(
                const FIncrementPurchaseCountTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>> Result
            ) override;
        };
        friend FIncrementPurchaseCountTask;

        TSharedPtr<FAsyncTask<FIncrementPurchaseCountTask>> IncrementPurchaseCount(
            Request::FIncrementPurchaseCountByUserIdRequestPtr Request
        );

        class GS2SHOWCASE_API FForceReDrawTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>>>,
            public TSharedFromThis<FForceReDrawTask>
        {
            const TSharedPtr<FRandomShowcaseStatusDomain> Self;
            const Request::FForceReDrawByUserIdRequestPtr Request;
        public:
            explicit FForceReDrawTask(
                const TSharedPtr<FRandomShowcaseStatusDomain> Self,
                const Request::FForceReDrawByUserIdRequestPtr Request
            );

            FForceReDrawTask(
                const FForceReDrawTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>>>> Result
            ) override;
        };
        friend FForceReDrawTask;

        TSharedPtr<FAsyncTask<FForceReDrawTask>> ForceReDraw(
            Request::FForceReDrawByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> ShowcaseName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ShowcaseName
        );

    };

    typedef TSharedPtr<FRandomShowcaseStatusDomain> FRandomShowcaseStatusDomainPtr;
}
