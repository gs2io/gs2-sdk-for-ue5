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
#include "Lottery/Gs2Lottery.h"
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

    class GS2LOTTERY_API FPrizeLimitDomain:
        public TSharedFromThis<FPrizeLimitDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Lottery::FGs2LotteryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> PrizeTableName;
        TOptional<FString> PrizeId;
    private:

        FString ParentKey;

    public:

        FPrizeLimitDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> PrizeTableName,
            const TOptional<FString> PrizeId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FPrizeLimitDomain(
            const FPrizeLimitDomain& From
        );

        class GS2LOTTERY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Model::FPrizeLimit>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FPrizeLimitDomain> Self;
            const Request::FGetPrizeLimitRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FPrizeLimitDomain> Self,
                const Request::FGetPrizeLimitRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeLimit>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetPrizeLimitRequestPtr Request
        );

        class GS2LOTTERY_API FResetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Domain::Model::FPrizeLimitDomain>,
            public TSharedFromThis<FResetTask>
        {
            const TSharedPtr<FPrizeLimitDomain> Self;
            const Request::FResetPrizeLimitRequestPtr Request;
        public:
            explicit FResetTask(
                const TSharedPtr<FPrizeLimitDomain> Self,
                const Request::FResetPrizeLimitRequestPtr Request
            );

            FResetTask(
                const FResetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeLimitDomain>> Result
            ) override;
        };
        friend FResetTask;

        TSharedPtr<FAsyncTask<FResetTask>> Reset(
            Request::FResetPrizeLimitRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> PrizeTableName,
            TOptional<FString> PrizeId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> PrizeId
        );

        class GS2LOTTERY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Model::FPrizeLimit>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FPrizeLimitDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FPrizeLimitDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeLimit>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FPrizeLimitDomain> FPrizeLimitDomainPtr;
}
