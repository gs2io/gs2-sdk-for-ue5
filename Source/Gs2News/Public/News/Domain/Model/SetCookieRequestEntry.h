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
#include "News/Domain/Iterator/DescribeNamespacesIterator.h"
#include "News/Domain/Iterator/DescribeProgressesIterator.h"
#include "News/Domain/Iterator/DescribeOutputsIterator.h"
#include "News/Domain/Iterator/DescribeNewsIterator.h"
#include "News/Domain/Iterator/DescribeNewsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::News::Domain
{
    class FGs2NewsDomain;
    typedef TSharedPtr<FGs2NewsDomain> FGs2NewsDomainPtr;
}

namespace Gs2::News::Domain::Model
{
    class FNamespaceDomain;
    class FProgressDomain;
    class FOutputDomain;
    class FCurrentNewsMasterDomain;
    class FNewsDomain;
    class FNewsAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FSetCookieRequestEntryDomain;

    class GS2NEWS_API FSetCookieRequestEntryDomain:
        public TSharedFromThis<FSetCookieRequestEntryDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const News::Domain::FGs2NewsDomainPtr Service;
        const Gs2::News::FGs2NewsRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> Key;
        TOptional<FString> Value;
    private:

        FString ParentKey;

    public:

        FSetCookieRequestEntryDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const News::Domain::FGs2NewsDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> Key,
            const TOptional<FString> Value
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSetCookieRequestEntryDomain(
            const FSetCookieRequestEntryDomain& From
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> Key,
            TOptional<FString> Value,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> Key,
            TOptional<FString> Value
        );

        class GS2NEWS_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::News::Model::FSetCookieRequestEntry>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSetCookieRequestEntryDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSetCookieRequestEntryDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::News::Model::FSetCookieRequestEntry>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::News::Model::FSetCookieRequestEntryPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FSetCookieRequestEntryDomain> FSetCookieRequestEntryDomainPtr;
}
