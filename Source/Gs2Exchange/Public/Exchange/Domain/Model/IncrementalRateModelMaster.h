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

    class GS2EXCHANGE_API FIncrementalRateModelMasterDomain:
        public TSharedFromThis<FIncrementalRateModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Exchange::FGs2ExchangeRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> RateName;
    private:

        FString ParentKey;

    public:

        FIncrementalRateModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> RateName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FIncrementalRateModelMasterDomain(
            const FIncrementalRateModelMasterDomain& From
        );

        class GS2EXCHANGE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Model::FIncrementalRateModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FIncrementalRateModelMasterDomain> Self;
            const Request::FGetIncrementalRateModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FIncrementalRateModelMasterDomain> Self,
                const Request::FGetIncrementalRateModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FIncrementalRateModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetIncrementalRateModelMasterRequestPtr Request
        );

        class GS2EXCHANGE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FIncrementalRateModelMasterDomain> Self;
            const Request::FUpdateIncrementalRateModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FIncrementalRateModelMasterDomain> Self,
                const Request::FUpdateIncrementalRateModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateIncrementalRateModelMasterRequestPtr Request
        );

        class GS2EXCHANGE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FIncrementalRateModelMasterDomain> Self;
            const Request::FDeleteIncrementalRateModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FIncrementalRateModelMasterDomain> Self,
                const Request::FDeleteIncrementalRateModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FIncrementalRateModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteIncrementalRateModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> RateName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> RateName
        );

        class GS2EXCHANGE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Model::FIncrementalRateModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FIncrementalRateModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FIncrementalRateModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FIncrementalRateModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FIncrementalRateModelMasterDomain> FIncrementalRateModelMasterDomainPtr;
}
