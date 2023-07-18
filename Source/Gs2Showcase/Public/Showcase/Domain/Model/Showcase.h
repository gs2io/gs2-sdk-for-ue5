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
    class FRandomShowcaseMasterDomain;
    class FRandomShowcaseDomain;
    class FRandomShowcaseAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FRandomShowcaseStatusDomain;
    class FRandomShowcaseStatusAccessTokenDomain;
    class FRandomDisplayItemDomain;
    class FRandomDisplayItemAccessTokenDomain;

    class GS2SHOWCASE_API FShowcaseDomain:
        public TSharedFromThis<FShowcaseDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
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
        TOptional<FString> UserId;
        TOptional<FString> ShowcaseName;
    private:

        FString ParentKey;

    public:

        FShowcaseDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> ShowcaseName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FShowcaseDomain(
            const FShowcaseDomain& From
        );

        class GS2SHOWCASE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FShowcase>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FShowcaseDomain> Self;
            const Request::FGetShowcaseByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FShowcaseDomain> Self,
                const Request::FGetShowcaseByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FShowcase>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetShowcaseByUserIdRequestPtr Request
        );

        class GS2SHOWCASE_API FBuyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Domain::Model::FShowcaseDomain>,
            public TSharedFromThis<FBuyTask>
        {
            const TSharedPtr<FShowcaseDomain> Self;
            const Request::FBuyByUserIdRequestPtr Request;
        public:
            explicit FBuyTask(
                const TSharedPtr<FShowcaseDomain> Self,
                const Request::FBuyByUserIdRequestPtr Request
            );

            FBuyTask(
                const FBuyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FShowcaseDomain>> Result
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
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ShowcaseName
        );

        class GS2SHOWCASE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FShowcase>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FShowcaseDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FShowcaseDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FShowcase>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FShowcaseDomain> FShowcaseDomainPtr;
}
