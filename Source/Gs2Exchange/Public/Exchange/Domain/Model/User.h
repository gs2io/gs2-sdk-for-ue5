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
#include "Exchange/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Exchange/Domain/Iterator/DescribeRateModelsIterator.h"
#include "Exchange/Domain/Iterator/DescribeRateModelMastersIterator.h"
#include "Exchange/Domain/Iterator/DescribeIncrementalRateModelsIterator.h"
#include "Exchange/Domain/Iterator/DescribeIncrementalRateModelMastersIterator.h"
#include "Exchange/Domain/Iterator/DescribeAwaitsIterator.h"
#include "Exchange/Domain/Iterator/DescribeAwaitsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Exchange::Domain
{
    class FGs2ExchangeDomain;
    typedef TSharedPtr<FGs2ExchangeDomain> FGs2ExchangeDomainPtr;
}

namespace Gs2::Exchange::Domain::Model
{
    class FNamespaceDomain;
    class FRateModelDomain;
    class FRateModelMasterDomain;
    class FIncrementalRateModelDomain;
    class FIncrementalRateModelMasterDomain;
    class FExchangeDomain;
    class FExchangeAccessTokenDomain;
    class FCurrentRateMasterDomain;
    class FAwaitDomain;
    class FAwaitAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2EXCHANGE_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Exchange::Domain::FGs2ExchangeDomainPtr Service;
        const Gs2::Exchange::FGs2ExchangeRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Exchange::Domain::FGs2ExchangeDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2EXCHANGE_API FCreateAwaitTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FAwaitDomain>,
            public TSharedFromThis<FCreateAwaitTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FCreateAwaitByUserIdRequestPtr Request;
        public:
            explicit FCreateAwaitTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FCreateAwaitByUserIdRequestPtr Request
            );

            FCreateAwaitTask(
                const FCreateAwaitTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
            ) override;
        };
        friend FCreateAwaitTask;

        TSharedPtr<FAsyncTask<FCreateAwaitTask>> CreateAwait(
            Request::FCreateAwaitByUserIdRequestPtr Request
        );

        TSharedPtr<Gs2::Exchange::Domain::Model::FExchangeDomain> Exchange(
        );

        Gs2::Exchange::Domain::Iterator::FDescribeAwaitsByUserIdIteratorPtr Awaits(
            const TOptional<FString> RateName = TOptional<FString>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeAwaits(
            TFunction<void()> Callback
        );

        void UnsubscribeAwaits(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain> Await(
            const FString AwaitName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
