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
#include "Exchange/Gs2Exchange.h"
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

    class GS2EXCHANGE_API FAwaitAccessTokenDomain:
        public TSharedFromThis<FAwaitAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Exchange::FGs2ExchangeRestClientPtr Client;

        public:
        TOptional<int64> UnlockAt;
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<int64> GetUnlockAt() const
        {
            return UnlockAt;
        }
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
        TOptional<FString> AwaitName;
    private:

        FString ParentKey;

    public:

        FAwaitAccessTokenDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> AwaitName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FAwaitAccessTokenDomain(
            const FAwaitAccessTokenDomain& From
        );

        class GS2EXCHANGE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Model::FAwait>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FAwaitAccessTokenDomain> Self;
            const Request::FGetAwaitRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FAwaitAccessTokenDomain> Self,
                const Request::FGetAwaitRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FAwait>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetAwaitRequestPtr Request
        );

        class GS2EXCHANGE_API FAcquireTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>,
            public TSharedFromThis<FAcquireTask>
        {
            const TSharedPtr<FAwaitAccessTokenDomain> Self;
            const Request::FAcquireRequestPtr Request;
        public:
            explicit FAcquireTask(
                const TSharedPtr<FAwaitAccessTokenDomain> Self,
                const Request::FAcquireRequestPtr Request
            );

            FAcquireTask(
                const FAcquireTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>> Result
            ) override;
        };
        friend FAcquireTask;

        TSharedPtr<FAsyncTask<FAcquireTask>> Acquire(
            Request::FAcquireRequestPtr Request
        );

        class GS2EXCHANGE_API FSkipTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>,
            public TSharedFromThis<FSkipTask>
        {
            const TSharedPtr<FAwaitAccessTokenDomain> Self;
            const Request::FSkipRequestPtr Request;
        public:
            explicit FSkipTask(
                const TSharedPtr<FAwaitAccessTokenDomain> Self,
                const Request::FSkipRequestPtr Request
            );

            FSkipTask(
                const FSkipTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>> Result
            ) override;
        };
        friend FSkipTask;

        TSharedPtr<FAsyncTask<FSkipTask>> Skip(
            Request::FSkipRequestPtr Request
        );

        class GS2EXCHANGE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FAwaitAccessTokenDomain> Self;
            const Request::FDeleteAwaitRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FAwaitAccessTokenDomain> Self,
                const Request::FDeleteAwaitRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteAwaitRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> AwaitName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> AwaitName
        );

        class GS2EXCHANGE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Model::FAwait>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FAwaitAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FAwaitAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FAwait>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Exchange::Model::FAwaitPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FAwaitAccessTokenDomain> FAwaitAccessTokenDomainPtr;
}
