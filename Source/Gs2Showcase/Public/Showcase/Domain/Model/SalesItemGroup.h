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

    class GS2SHOWCASE_API FSalesItemGroupDomain:
        public TSharedFromThis<FSalesItemGroupDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> DisplayItemId;
    private:

        FString ParentKey;

    public:

        FSalesItemGroupDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> DisplayItemId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSalesItemGroupDomain(
            const FSalesItemGroupDomain& From
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> DisplayItemId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2SHOWCASE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Showcase::Model::FSalesItemGroup>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSalesItemGroupDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSalesItemGroupDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FSalesItemGroup>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FSalesItemGroupDomain> FSalesItemGroupDomainPtr;
}
