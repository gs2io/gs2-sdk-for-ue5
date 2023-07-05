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

    class GS2EXCHANGE_API FExchangeAccessTokenDomain:
        public TSharedFromThis<FExchangeAccessTokenDomain>
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
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FExchangeAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FExchangeAccessTokenDomain(
            const FExchangeAccessTokenDomain& From
        );

        class GS2EXCHANGE_API FExchangeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FExchangeAccessTokenDomain>,
            public TSharedFromThis<FExchangeTask>
        {
            const TSharedPtr<FExchangeAccessTokenDomain> Self;
            const Request::FExchangeRequestPtr Request;
        public:
            explicit FExchangeTask(
                const TSharedPtr<FExchangeAccessTokenDomain> Self,
                const Request::FExchangeRequestPtr Request
            );

            FExchangeTask(
                const FExchangeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FExchangeAccessTokenDomain>> Result
            ) override;
        };
        friend FExchangeTask;

        TSharedPtr<FAsyncTask<FExchangeTask>> Exchange(
            Request::FExchangeRequestPtr Request
        );

        class GS2EXCHANGE_API FIncrementalTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FExchangeAccessTokenDomain>,
            public TSharedFromThis<FIncrementalTask>
        {
            const TSharedPtr<FExchangeAccessTokenDomain> Self;
            const Request::FIncrementalExchangeRequestPtr Request;
        public:
            explicit FIncrementalTask(
                const TSharedPtr<FExchangeAccessTokenDomain> Self,
                const Request::FIncrementalExchangeRequestPtr Request
            );

            FIncrementalTask(
                const FIncrementalTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FExchangeAccessTokenDomain>> Result
            ) override;
        };
        friend FIncrementalTask;

        TSharedPtr<FAsyncTask<FIncrementalTask>> Incremental(
            Request::FIncrementalExchangeRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

    };

    typedef TSharedPtr<FExchangeAccessTokenDomain> FExchangeAccessTokenDomainPtr;
}
