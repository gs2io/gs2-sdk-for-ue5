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

    class GS2SHOWCASE_API FRandomDisplayItemDomain:
        public TSharedFromThis<FRandomDisplayItemDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Showcase::Domain::FGs2ShowcaseDomainPtr Service;
        const Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

        public:
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> ShowcaseName;
        TOptional<FString> DisplayItemName;
    private:

        FString ParentKey;

    public:

        FRandomDisplayItemDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> ShowcaseName,
            const TOptional<FString> DisplayItemName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRandomDisplayItemDomain(
            const FRandomDisplayItemDomain& From
        );

        class GS2SHOWCASE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FRandomDisplayItem>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRandomDisplayItemDomain> Self;
            const Request::FGetRandomDisplayItemByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRandomDisplayItemDomain>& Self,
                const Request::FGetRandomDisplayItemByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetRandomDisplayItemByUserIdRequestPtr Request
        );

        class GS2SHOWCASE_API FRandomShowcaseBuyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>,
            public TSharedFromThis<FRandomShowcaseBuyTask>
        {
            const TSharedPtr<FRandomDisplayItemDomain> Self;
            const Request::FRandomShowcaseBuyByUserIdRequestPtr Request;
        public:
            explicit FRandomShowcaseBuyTask(
                const TSharedPtr<FRandomDisplayItemDomain>& Self,
                const Request::FRandomShowcaseBuyByUserIdRequestPtr Request
            );

            FRandomShowcaseBuyTask(
                const FRandomShowcaseBuyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>> Result
            ) override;
        };
        friend FRandomShowcaseBuyTask;

        TSharedPtr<FAsyncTask<FRandomShowcaseBuyTask>> RandomShowcaseBuy(
            Request::FRandomShowcaseBuyByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> ShowcaseName,
            TOptional<FString> DisplayItemName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> DisplayItemName
        );

        class GS2SHOWCASE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FRandomDisplayItem>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FRandomDisplayItemDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRandomDisplayItemDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Showcase::Model::FRandomDisplayItemPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FRandomDisplayItemDomain> FRandomDisplayItemDomainPtr;
}
