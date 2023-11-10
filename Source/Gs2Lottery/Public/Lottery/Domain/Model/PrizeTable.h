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
#include "Lottery/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Lottery/Domain/Iterator/DescribeLotteryModelMastersIterator.h"
#include "Lottery/Domain/Iterator/DescribePrizeTableMastersIterator.h"
#include "Lottery/Domain/Iterator/DescribeLotteryModelsIterator.h"
#include "Lottery/Domain/Iterator/DescribePrizeTablesIterator.h"
#include "Lottery/Domain/Iterator/DescribeProbabilitiesIterator.h"
#include "Lottery/Domain/Iterator/DescribeProbabilitiesByUserIdIterator.h"
#include "Lottery/Domain/Iterator/DescribePrizeLimitsIterator.h"
#include "Lottery/Domain/Iterator/DescribeBoxesIterator.h"
#include "Lottery/Domain/Iterator/DescribeBoxesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Lottery::Domain
{
    class FGs2LotteryDomain;
    typedef TSharedPtr<FGs2LotteryDomain> FGs2LotteryDomainPtr;
}

namespace Gs2::Lottery::Domain::Model
{
    class FNamespaceDomain;
    class FLotteryModelMasterDomain;
    class FPrizeTableMasterDomain;
    class FLotteryModelDomain;
    class FPrizeTableDomain;
    class FLotteryDomain;
    class FLotteryAccessTokenDomain;
    class FProbabilityDomain;
    class FProbabilityAccessTokenDomain;
    class FCurrentLotteryMasterDomain;
    class FPrizeLimitDomain;
    class FBoxItemsDomain;
    class FBoxItemsAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2LOTTERY_API FPrizeTableDomain:
        public TSharedFromThis<FPrizeTableDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Lottery::Domain::FGs2LotteryDomainPtr Service;
        const Gs2::Lottery::FGs2LotteryRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> PrizeTableName;
    private:

        FString ParentKey;

    public:

        FPrizeTableDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Lottery::Domain::FGs2LotteryDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> PrizeTableName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FPrizeTableDomain(
            const FPrizeTableDomain& From
        );

        class GS2LOTTERY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Model::FPrizeTable>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FPrizeTableDomain> Self;
            const Request::FGetPrizeTableRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FPrizeTableDomain>& Self,
                const Request::FGetPrizeTableRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeTable>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetPrizeTableRequestPtr Request
        );

        Gs2::Lottery::Domain::Iterator::FDescribePrizeLimitsIteratorPtr PrizeLimits(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribePrizeLimits(
            TFunction<void()> Callback
        );

        void UnsubscribePrizeLimits(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeLimitDomain> PrizeLimit(
            const FString PrizeId
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> PrizeTableName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> PrizeTableName
        );

        class GS2LOTTERY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Model::FPrizeTable>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FPrizeTableDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FPrizeTableDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeTable>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Lottery::Model::FPrizeTablePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FPrizeTableDomain> FPrizeTableDomainPtr;
}
