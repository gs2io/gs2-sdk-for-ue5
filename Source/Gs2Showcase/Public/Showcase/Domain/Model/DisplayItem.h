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
#include "Showcase/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Showcase/Domain/Iterator/DescribeSalesItemMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeSalesItemGroupMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcaseMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcasesIterator.h"
#include "Showcase/Domain/Iterator/DescribeShowcasesByUserIdIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomShowcaseMastersIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomDisplayItemsIterator.h"
#include "Showcase/Domain/Iterator/DescribeRandomDisplayItemsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Showcase::Domain
{
    class FGs2ShowcaseDomain;
    typedef TSharedPtr<FGs2ShowcaseDomain> FGs2ShowcaseDomainPtr;
}

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

    class GS2SHOWCASE_API FDisplayItemDomain:
        public TSharedFromThis<FDisplayItemDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Showcase::Domain::FGs2ShowcaseDomainPtr Service;
        const Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> ShowcaseName;
        TOptional<FString> DisplayItemId;
    private:

        FString ParentKey;

    public:

        FDisplayItemDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> ShowcaseName,
            const TOptional<FString> DisplayItemId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FDisplayItemDomain(
            const FDisplayItemDomain& From
        );

        class GS2SHOWCASE_API FBuyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionDomain>,
            public TSharedFromThis<FBuyTask>
        {
            const TSharedPtr<FDisplayItemDomain> Self;
            const Request::FBuyByUserIdRequestPtr Request;
        public:
            explicit FBuyTask(
                const TSharedPtr<FDisplayItemDomain>& Self,
                const Request::FBuyByUserIdRequestPtr Request
            );

            FBuyTask(
                const FBuyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
            ) override;
        };
        friend FBuyTask;

        TSharedPtr<FAsyncTask<FBuyTask>> Buy(
            Request::FBuyByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> ShowcaseName,
            TOptional<FString> DisplayItemId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> DisplayItemId
        );

        class GS2SHOWCASE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FDisplayItem>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FDisplayItemDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FDisplayItemDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FDisplayItem>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Showcase::Model::FDisplayItemPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FDisplayItemDomain> FDisplayItemDomainPtr;
}
