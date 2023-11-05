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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
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

    class GS2SHOWCASE_API FRandomDisplayItemAccessTokenDomain:
        public TSharedFromThis<FRandomDisplayItemAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

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
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> ShowcaseName;
        TOptional<FString> DisplayItemName;
    private:

        FString ParentKey;

    public:

        FRandomDisplayItemAccessTokenDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> ShowcaseName,
            const TOptional<FString> DisplayItemName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRandomDisplayItemAccessTokenDomain(
            const FRandomDisplayItemAccessTokenDomain& From
        );

        class GS2SHOWCASE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FRandomDisplayItem>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRandomDisplayItemAccessTokenDomain> Self;
            const Request::FGetRandomDisplayItemRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRandomDisplayItemAccessTokenDomain> Self,
                const Request::FGetRandomDisplayItemRequestPtr Request
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
            Request::FGetRandomDisplayItemRequestPtr Request
        );

        class GS2SHOWCASE_API FRandomShowcaseBuyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FRandomDisplayItemAccessTokenDomain>,
            public TSharedFromThis<FRandomShowcaseBuyTask>
        {
            const TSharedPtr<FRandomDisplayItemAccessTokenDomain> Self;
            const Request::FRandomShowcaseBuyRequestPtr Request;
        public:
            explicit FRandomShowcaseBuyTask(
                const TSharedPtr<FRandomDisplayItemAccessTokenDomain> Self,
                const Request::FRandomShowcaseBuyRequestPtr Request
            );

            FRandomShowcaseBuyTask(
                const FRandomShowcaseBuyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemAccessTokenDomain>> Result
            ) override;
        };
        friend FRandomShowcaseBuyTask;

        TSharedPtr<FAsyncTask<FRandomShowcaseBuyTask>> RandomShowcaseBuy(
            Request::FRandomShowcaseBuyRequestPtr Request
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
            const TSharedPtr<FRandomDisplayItemAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRandomDisplayItemAccessTokenDomain> Self
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

    typedef TSharedPtr<FRandomDisplayItemAccessTokenDomain> FRandomDisplayItemAccessTokenDomainPtr;
}
