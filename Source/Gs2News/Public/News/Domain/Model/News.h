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

    class GS2NEWS_API FNewsDomain:
        public TSharedFromThis<FNewsDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const News::Domain::FGs2NewsDomainPtr Service;
        const Gs2::News::FGs2NewsRestClientPtr Client;

        public:
        TOptional<FString> BrowserUrl;
        TOptional<FString> ZipUrl;
        TOptional<FString> GetBrowserUrl() const
        {
            return BrowserUrl;
        }
        TOptional<FString> GetZipUrl() const
        {
            return ZipUrl;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FNewsDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const News::Domain::FGs2NewsDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNewsDomain(
            const FNewsDomain& From
        );

        class GS2NEWS_API FWantGrantTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::News::Domain::Model::FSetCookieRequestEntryDomain>>>,
            public TSharedFromThis<FWantGrantTask>
        {
            const TSharedPtr<FNewsDomain> Self;
            const Request::FWantGrantByUserIdRequestPtr Request;
        public:
            explicit FWantGrantTask(
                const TSharedPtr<FNewsDomain>& Self,
                const Request::FWantGrantByUserIdRequestPtr Request
            );

            FWantGrantTask(
                const FWantGrantTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::News::Domain::Model::FSetCookieRequestEntryDomain>>>> Result
            ) override;
        };
        friend FWantGrantTask;

        TSharedPtr<FAsyncTask<FWantGrantTask>> WantGrant(
            Request::FWantGrantByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2NEWS_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::News::Model::FNews>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNewsDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNewsDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::News::Model::FNews>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::News::Model::FNewsPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNewsDomain> FNewsDomainPtr;
}
