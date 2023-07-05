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

    class GS2EXCHANGE_API FExchangeDomain:
        public TSharedFromThis<FExchangeDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Exchange::FGs2ExchangeRestClientPtr Client;

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
    private:

        FString ParentKey;

    public:

        FExchangeDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FExchangeDomain(
            const FExchangeDomain& From
        );

        class GS2EXCHANGE_API FExchangeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FExchangeDomain>,
            public TSharedFromThis<FExchangeTask>
        {
            const TSharedPtr<FExchangeDomain> Self;
            const Request::FExchangeByUserIdRequestPtr Request;
        public:
            explicit FExchangeTask(
                const TSharedPtr<FExchangeDomain> Self,
                const Request::FExchangeByUserIdRequestPtr Request
            );

            FExchangeTask(
                const FExchangeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FExchangeDomain>> Result
            ) override;
        };
        friend FExchangeTask;

        TSharedPtr<FAsyncTask<FExchangeTask>> Exchange(
            Request::FExchangeByUserIdRequestPtr Request
        );

        class GS2EXCHANGE_API FIncrementalTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FExchangeDomain>,
            public TSharedFromThis<FIncrementalTask>
        {
            const TSharedPtr<FExchangeDomain> Self;
            const Request::FIncrementalExchangeByUserIdRequestPtr Request;
        public:
            explicit FIncrementalTask(
                const TSharedPtr<FExchangeDomain> Self,
                const Request::FIncrementalExchangeByUserIdRequestPtr Request
            );

            FIncrementalTask(
                const FIncrementalTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FExchangeDomain>> Result
            ) override;
        };
        friend FIncrementalTask;

        TSharedPtr<FAsyncTask<FIncrementalTask>> Incremental(
            Request::FIncrementalExchangeByUserIdRequestPtr Request
        );

        class GS2EXCHANGE_API FUnlockIncrementalTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FIncrementalRateModelDomain>,
            public TSharedFromThis<FUnlockIncrementalTask>
        {
            const TSharedPtr<FExchangeDomain> Self;
            const Request::FUnlockIncrementalExchangeByUserIdRequestPtr Request;
        public:
            explicit FUnlockIncrementalTask(
                const TSharedPtr<FExchangeDomain> Self,
                const Request::FUnlockIncrementalExchangeByUserIdRequestPtr Request
            );

            FUnlockIncrementalTask(
                const FUnlockIncrementalTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FIncrementalRateModelDomain>> Result
            ) override;
        };
        friend FUnlockIncrementalTask;

        TSharedPtr<FAsyncTask<FUnlockIncrementalTask>> UnlockIncremental(
            Request::FUnlockIncrementalExchangeByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

    };

    typedef TSharedPtr<FExchangeDomain> FExchangeDomainPtr;
}
