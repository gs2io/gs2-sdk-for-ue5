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

    class GS2EXCHANGE_API FAwaitDomain:
        public TSharedFromThis<FAwaitDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
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
        TOptional<FString> UserId;
        TOptional<FString> AwaitName;
    private:

        FString ParentKey;

    public:

        FAwaitDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> AwaitName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FAwaitDomain(
            const FAwaitDomain& From
        );

        class GS2EXCHANGE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Model::FAwait>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FAwaitDomain> Self;
            const Request::FGetAwaitByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FAwaitDomain> Self,
                const Request::FGetAwaitByUserIdRequestPtr Request
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
            Request::FGetAwaitByUserIdRequestPtr Request
        );

        class GS2EXCHANGE_API FAcquireTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FAwaitDomain>,
            public TSharedFromThis<FAcquireTask>
        {
            const TSharedPtr<FAwaitDomain> Self;
            const Request::FAcquireByUserIdRequestPtr Request;
        public:
            explicit FAcquireTask(
                const TSharedPtr<FAwaitDomain> Self,
                const Request::FAcquireByUserIdRequestPtr Request
            );

            FAcquireTask(
                const FAcquireTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
            ) override;
        };
        friend FAcquireTask;

        TSharedPtr<FAsyncTask<FAcquireTask>> Acquire(
            Request::FAcquireByUserIdRequestPtr Request
        );

        class GS2EXCHANGE_API FAcquireForceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FAwaitDomain>,
            public TSharedFromThis<FAcquireForceTask>
        {
            const TSharedPtr<FAwaitDomain> Self;
            const Request::FAcquireForceByUserIdRequestPtr Request;
        public:
            explicit FAcquireForceTask(
                const TSharedPtr<FAwaitDomain> Self,
                const Request::FAcquireForceByUserIdRequestPtr Request
            );

            FAcquireForceTask(
                const FAcquireForceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
            ) override;
        };
        friend FAcquireForceTask;

        TSharedPtr<FAsyncTask<FAcquireForceTask>> AcquireForce(
            Request::FAcquireForceByUserIdRequestPtr Request
        );

        class GS2EXCHANGE_API FSkipTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FAwaitDomain>,
            public TSharedFromThis<FSkipTask>
        {
            const TSharedPtr<FAwaitDomain> Self;
            const Request::FSkipByUserIdRequestPtr Request;
        public:
            explicit FSkipTask(
                const TSharedPtr<FAwaitDomain> Self,
                const Request::FSkipByUserIdRequestPtr Request
            );

            FSkipTask(
                const FSkipTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
            ) override;
        };
        friend FSkipTask;

        TSharedPtr<FAsyncTask<FSkipTask>> Skip(
            Request::FSkipByUserIdRequestPtr Request
        );

        class GS2EXCHANGE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FAwaitDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FAwaitDomain> Self;
            const Request::FDeleteAwaitByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FAwaitDomain> Self,
                const Request::FDeleteAwaitByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteAwaitByUserIdRequestPtr Request
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
            const TSharedPtr<FAwaitDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FAwaitDomain> Self
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

    };

    typedef TSharedPtr<FAwaitDomain> FAwaitDomainPtr;
}
