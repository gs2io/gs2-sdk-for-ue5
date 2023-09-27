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

    class GS2LOTTERY_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Lottery::FGs2LotteryRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2LOTTERY_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2LOTTERY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2LOTTERY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2LOTTERY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2LOTTERY_API FCreatePrizeTableMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain>,
            public TSharedFromThis<FCreatePrizeTableMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreatePrizeTableMasterRequestPtr Request;
        public:
            explicit FCreatePrizeTableMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreatePrizeTableMasterRequestPtr Request
            );

            FCreatePrizeTableMasterTask(
                const FCreatePrizeTableMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain>> Result
            ) override;
        };
        friend FCreatePrizeTableMasterTask;

        TSharedPtr<FAsyncTask<FCreatePrizeTableMasterTask>> CreatePrizeTableMaster(
            Request::FCreatePrizeTableMasterRequestPtr Request
        );

        class GS2LOTTERY_API FCreateLotteryModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Domain::Model::FLotteryModelMasterDomain>,
            public TSharedFromThis<FCreateLotteryModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateLotteryModelMasterRequestPtr Request;
        public:
            explicit FCreateLotteryModelMasterTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateLotteryModelMasterRequestPtr Request
            );

            FCreateLotteryModelMasterTask(
                const FCreateLotteryModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FLotteryModelMasterDomain>> Result
            ) override;
        };
        friend FCreateLotteryModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateLotteryModelMasterTask>> CreateLotteryModelMaster(
            Request::FCreateLotteryModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Lottery::Domain::Model::FUserDomain> User(
            const FString UserId
        ) const;

        TSharedPtr<Gs2::Lottery::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        ) const;

        TSharedPtr<Gs2::Lottery::Domain::Model::FCurrentLotteryMasterDomain> CurrentLotteryMaster(
        ) const;

        Gs2::Lottery::Domain::Iterator::FDescribePrizeTablesIteratorPtr PrizeTables(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribePrizeTables(
            TFunction<void()> Callback
        );

        void UnsubscribePrizeTables(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeTableDomain> PrizeTable(
            const FString PrizeTableName
        ) const;

        Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIteratorPtr LotteryModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLotteryModels(
            TFunction<void()> Callback
        );

        void UnsubscribeLotteryModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Lottery::Domain::Model::FLotteryModelDomain> LotteryModel(
            const FString LotteryName
        ) const;

        Gs2::Lottery::Domain::Iterator::FDescribePrizeTableMastersIteratorPtr PrizeTableMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribePrizeTableMasters(
            TFunction<void()> Callback
        );

        void UnsubscribePrizeTableMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain> PrizeTableMaster(
            const FString PrizeTableName
        ) const;

        Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelMastersIteratorPtr LotteryModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLotteryModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeLotteryModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Lottery::Domain::Model::FLotteryModelMasterDomain> LotteryModelMaster(
            const FString LotteryName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2LOTTERY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Lottery::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Lottery::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
