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
#include "Money2/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Money2/Domain/Iterator/DescribeWalletsIterator.h"
#include "Money2/Domain/Iterator/DescribeWalletsByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeEventsByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelsIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelMastersIterator.h"
#include "Money2/Domain/Iterator/DescribeDailyTransactionHistoriesByCurrencyIterator.h"
#include "Money2/Domain/Iterator/DescribeDailyTransactionHistoriesIterator.h"
#include "Money2/Domain/Iterator/DescribeUnusedBalancesIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Money2::Domain
{
    class FGs2Money2Domain;
    typedef TSharedPtr<FGs2Money2Domain> FGs2Money2DomainPtr;
}

namespace Gs2::Money2::Domain::Model
{
    class FNamespaceDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FWalletDomain;
    class FWalletAccessTokenDomain;
    class FEventDomain;
    class FEventAccessTokenDomain;
    class FStoreContentModelDomain;
    class FStoreContentModelMasterDomain;
    class FCurrentModelMasterDomain;
    class FDailyTransactionHistoryDomain;
    class FUnusedBalanceDomain;

    class GS2MONEY2_API FUnusedBalanceDomain:
        public TSharedFromThis<FUnusedBalanceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Money2::Domain::FGs2Money2DomainPtr Service;
        const Gs2::Money2::FGs2Money2RestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> Currency;
    private:

        FString ParentKey;

    public:

        FUnusedBalanceDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Money2::Domain::FGs2Money2DomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> Currency
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUnusedBalanceDomain(
            const FUnusedBalanceDomain& From
        );

        class GS2MONEY2_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Model::FUnusedBalance>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FUnusedBalanceDomain> Self;
            const Request::FGetUnusedBalanceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FUnusedBalanceDomain>& Self,
                const Request::FGetUnusedBalanceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Model::FUnusedBalance>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetUnusedBalanceRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> Currency,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> Currency
        );

        class GS2MONEY2_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Model::FUnusedBalance>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FUnusedBalanceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FUnusedBalanceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Model::FUnusedBalance>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Money2::Model::FUnusedBalancePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FUnusedBalanceDomain> FUnusedBalanceDomainPtr;
}