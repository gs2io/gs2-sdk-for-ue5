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

    class GS2LOTTERY_API FPrizeTableMasterDomain:
        public TSharedFromThis<FPrizeTableMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Lottery::Domain::FGs2LotteryDomainPtr Service;
        const Gs2::Lottery::FGs2LotteryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> PrizeTableName;
    private:

        FString ParentKey;

    public:

        FPrizeTableMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Lottery::Domain::FGs2LotteryDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> PrizeTableName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FPrizeTableMasterDomain(
            const FPrizeTableMasterDomain& From
        );

        class GS2LOTTERY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Model::FPrizeTableMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FPrizeTableMasterDomain> Self;
            const Request::FGetPrizeTableMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FPrizeTableMasterDomain>& Self,
                const Request::FGetPrizeTableMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeTableMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetPrizeTableMasterRequestPtr Request
        );

        class GS2LOTTERY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FPrizeTableMasterDomain> Self;
            const Request::FUpdatePrizeTableMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FPrizeTableMasterDomain>& Self,
                const Request::FUpdatePrizeTableMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdatePrizeTableMasterRequestPtr Request
        );

        class GS2LOTTERY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FPrizeTableMasterDomain> Self;
            const Request::FDeletePrizeTableMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FPrizeTableMasterDomain>& Self,
                const Request::FDeletePrizeTableMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeletePrizeTableMasterRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Model::FPrizeTableMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FPrizeTableMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FPrizeTableMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeTableMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Lottery::Model::FPrizeTableMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FPrizeTableMasterDomain> FPrizeTableMasterDomainPtr;
}
