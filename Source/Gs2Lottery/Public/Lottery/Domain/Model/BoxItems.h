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

    class GS2LOTTERY_API FBoxItemsDomain:
        public TSharedFromThis<FBoxItemsDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Lottery::FGs2LotteryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> PrizeTableName;
    private:

        FString ParentKey;

    public:

        FBoxItemsDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> PrizeTableName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBoxItemsDomain(
            const FBoxItemsDomain& From
        );

        class GS2LOTTERY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Model::FBoxItems>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FBoxItemsDomain> Self;
            const Request::FGetBoxByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FBoxItemsDomain> Self,
                const Request::FGetBoxByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FBoxItems>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetBoxByUserIdRequestPtr Request
        );

        class GS2LOTTERY_API FResetBoxTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Domain::Model::FBoxItemsDomain>,
            public TSharedFromThis<FResetBoxTask>
        {
            const TSharedPtr<FBoxItemsDomain> Self;
            const Request::FResetBoxByUserIdRequestPtr Request;
        public:
            explicit FResetBoxTask(
                const TSharedPtr<FBoxItemsDomain> Self,
                const Request::FResetBoxByUserIdRequestPtr Request
            );

            FResetBoxTask(
                const FResetBoxTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FBoxItemsDomain>> Result
            ) override;
        };
        friend FResetBoxTask;

        TSharedPtr<FAsyncTask<FResetBoxTask>> ResetBox(
            Request::FResetBoxByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> PrizeTableName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> PrizeTableName
        );

        class GS2LOTTERY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Model::FBoxItems>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FBoxItemsDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FBoxItemsDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FBoxItems>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FBoxItemsDomain> FBoxItemsDomainPtr;
}
