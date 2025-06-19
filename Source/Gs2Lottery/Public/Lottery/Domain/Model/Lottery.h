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
 *
 * deny overwrite
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

    class GS2LOTTERY_API FLotteryDomain:
        public TSharedFromThis<FLotteryDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Lottery::Domain::FGs2LotteryDomainPtr Service;
        const Gs2::Lottery::FGs2LotteryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> LotteryName;
    private:

        FString ParentKey;

    public:

        FLotteryDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Lottery::Domain::FGs2LotteryDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> LotteryName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FLotteryDomain(
            const FLotteryDomain& From
        );

        class GS2LOTTERY_API FDrawTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionDomain>,
            public TSharedFromThis<FDrawTask>
        {
            const TSharedPtr<FLotteryDomain> Self;
            const Request::FDrawByUserIdRequestPtr Request;
        public:
            explicit FDrawTask(
                const TSharedPtr<FLotteryDomain>& Self,
                const Request::FDrawByUserIdRequestPtr Request
            );

            FDrawTask(
                const FDrawTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
            ) override;
        };
        friend FDrawTask;

        TSharedPtr<FAsyncTask<FDrawTask>> Draw(
            Request::FDrawByUserIdRequestPtr Request
        );

        class GS2LOTTERY_API FPredictionTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Lottery::Model::FDrawnPrize>>>,
            public TSharedFromThis<FPredictionTask>
        {
            const TSharedPtr<FLotteryDomain> Self;
            const Request::FPredictionByUserIdRequestPtr Request;
        public:
            explicit FPredictionTask(
                const TSharedPtr<FLotteryDomain>& Self,
                const Request::FPredictionByUserIdRequestPtr Request
            );

            FPredictionTask(
                const FPredictionTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Lottery::Model::FDrawnPrize>>>> Result
            ) override;
        };
        friend FPredictionTask;

        TSharedPtr<FAsyncTask<FPredictionTask>> Prediction(
            Request::FPredictionByUserIdRequestPtr Request
        );

        class GS2LOTTERY_API FDrawWithRandomSeedTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionDomain>,
            public TSharedFromThis<FDrawWithRandomSeedTask>
        {
            const TSharedPtr<FLotteryDomain> Self;
            const Request::FDrawWithRandomSeedByUserIdRequestPtr Request;
        public:
            explicit FDrawWithRandomSeedTask(
                const TSharedPtr<FLotteryDomain>& Self,
                const Request::FDrawWithRandomSeedByUserIdRequestPtr Request
            );

            FDrawWithRandomSeedTask(
                const FDrawWithRandomSeedTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
            ) override;
        };
        friend FDrawWithRandomSeedTask;

        TSharedPtr<FAsyncTask<FDrawWithRandomSeedTask>> DrawWithRandomSeed(
            Request::FDrawWithRandomSeedByUserIdRequestPtr Request
        );

        Gs2::Lottery::Domain::Iterator::FDescribeProbabilitiesByUserIdIteratorPtr Probabilities(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeProbabilities(
            TFunction<void()> Callback
        );

        void UnsubscribeProbabilities(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> LotteryName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> LotteryName
        );

    };

    typedef TSharedPtr<FLotteryDomain> FLotteryDomainPtr;
}
