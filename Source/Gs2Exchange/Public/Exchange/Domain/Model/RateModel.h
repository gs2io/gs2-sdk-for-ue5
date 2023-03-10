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
#include "Exchange/Domain/Iterator/DescribeAwaitsIterator.h"
#include "Exchange/Domain/Iterator/DescribeAwaitsByUserIdIterator.h"

namespace Gs2::Exchange::Domain::Model
{
    class FNamespaceDomain;
    class FRateModelDomain;
    class FRateModelMasterDomain;
    class FExchangeDomain;
    class FExchangeAccessTokenDomain;
    class FCurrentRateMasterDomain;
    class FAwaitDomain;
    class FAwaitAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2EXCHANGE_API FRateModelDomain:
        public TSharedFromThis<FRateModelDomain>
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

        FRateModelDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> RateName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRateModelDomain(
            const FRateModelDomain& From
        );

        class GS2EXCHANGE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Model::FRateModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRateModelDomain> Self;
            const Request::FGetRateModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRateModelDomain> Self,
                const Request::FGetRateModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FRateModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetRateModelRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Model::FRateModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FRateModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRateModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FRateModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FRateModelDomain> FRateModelDomainPtr;
}
