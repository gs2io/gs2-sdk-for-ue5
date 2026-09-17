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
#include "Money2/Domain/Iterator/DescribeSubscriptionStatusesIterator.h"
#include "Money2/Domain/Iterator/DescribeSubscriptionStatusesByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeRefundHistoriesByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeRefundHistoriesByDateIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelsIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelMastersIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreSubscriptionContentModelsIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreSubscriptionContentModelMastersIterator.h"
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
    class FSubscriptionStatusDomain;
    class FSubscriptionStatusAccessTokenDomain;
    class FRefundHistoryDomain;
    class FStoreContentModelDomain;
    class FStoreContentModelMasterDomain;
    class FStoreSubscriptionContentModelDomain;
    class FStoreSubscriptionContentModelMasterDomain;
    class FCurrentModelMasterDomain;
    class FDailyTransactionHistoryDomain;
    class FUnusedBalanceDomain;

    class GS2MONEY2_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Money2::Domain::FGs2Money2DomainPtr Service;
        const Gs2::Money2::FGs2Money2RestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> Url;
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
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
            const Core::Domain::FGs2Ptr& Gs2,
            const Money2::Domain::FGs2Money2DomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );



        class GS2MONEY2_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );



        class GS2MONEY2_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );



        class GS2MONEY2_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );



        class GS2MONEY2_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );



        class GS2MONEY2_API FCreateStoreContentModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain>,
            public TSharedFromThis<FCreateStoreContentModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateStoreContentModelMasterRequestPtr Request;
        public:
            explicit FCreateStoreContentModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateStoreContentModelMasterRequestPtr Request
            );

            FCreateStoreContentModelMasterTask(
                const FCreateStoreContentModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain>> Result
            ) override;
        };
        friend FCreateStoreContentModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateStoreContentModelMasterTask>> CreateStoreContentModelMaster(
            Request::FCreateStoreContentModelMasterRequestPtr Request
        );



        class GS2MONEY2_API FCreateStoreSubscriptionContentModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>,
            public TSharedFromThis<FCreateStoreSubscriptionContentModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateStoreSubscriptionContentModelMasterRequestPtr Request;
        public:
            explicit FCreateStoreSubscriptionContentModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateStoreSubscriptionContentModelMasterRequestPtr Request
            );

            FCreateStoreSubscriptionContentModelMasterTask(
                const FCreateStoreSubscriptionContentModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>> Result
            ) override;
        };
        friend FCreateStoreSubscriptionContentModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateStoreSubscriptionContentModelMasterTask>> CreateStoreSubscriptionContentModelMaster(
            Request::FCreateStoreSubscriptionContentModelMasterRequestPtr Request
        );

        Gs2::Money2::Domain::Iterator::FDescribeDailyTransactionHistoriesByCurrencyIteratorPtr DailyTransactionHistoriesByCurrency(
            const FString Currency,
            const int32 Year,
            const TOptional<int32> Month = TOptional<int32>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDailyTransactionHistoriesByCurrency(
            TFunction<void()> Callback
            , const int32 Year, const TOptional<int32> Month = TOptional<int32>()
        );

        class FCollectDailyTransactionHistoriesByCurrencyTask;

        Gs2::Core::Domain::CallbackID SubscribeDailyTransactionHistoriesByCurrency(
            TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const FString Currency,const int32 Year,const TOptional<int32> Month = TOptional<int32>()
        );

        void InvalidateDailyTransactionHistoriesByCurrency(const FString Currency,const int32 Year,const TOptional<int32> Month = TOptional<int32>());

        class GS2MONEY2_API FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback;
        const FString QueryCurrency;const int32 QueryYear;const TOptional<int32> QueryMonth;
        public:
            FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const FString Currency,const int32 Year,const TOptional<int32> Month);
            FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask(const FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask>> SubscribeDailyTransactionHistoriesByCurrencyWithInitialCall(
            TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const FString Currency,const int32 Year,const TOptional<int32> Month = TOptional<int32>()
        );
        void UnsubscribeDailyTransactionHistoriesByCurrency(
            const int32 Year
            , Gs2::Core::Domain::CallbackID CallbackID, const FString Currency = FString(), const TOptional<int32> Month = TOptional<int32>()
        );

        Gs2::Money2::Domain::Iterator::FDescribeDailyTransactionHistoriesIteratorPtr DailyTransactionHistories(
            const int32 Year,
            const TOptional<int32> Month = TOptional<int32>(),
            const TOptional<int32> Day = TOptional<int32>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDailyTransactionHistories(
            TFunction<void()> Callback
            , const int32 Year, const TOptional<int32> Month = TOptional<int32>(), const TOptional<int32> Day = TOptional<int32>()
        );

        class FCollectDailyTransactionHistoriesTask;

        Gs2::Core::Domain::CallbackID SubscribeDailyTransactionHistories(
            TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const int32 Year,const TOptional<int32> Month = TOptional<int32>(),const TOptional<int32> Day = TOptional<int32>()
        );

        void InvalidateDailyTransactionHistories(const int32 Year,const TOptional<int32> Month = TOptional<int32>(),const TOptional<int32> Day = TOptional<int32>());

        class GS2MONEY2_API FSubscribeDailyTransactionHistoriesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeDailyTransactionHistoriesWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback;
        const int32 QueryYear;const TOptional<int32> QueryMonth;const TOptional<int32> QueryDay;
        public:
            FSubscribeDailyTransactionHistoriesWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const int32 Year,const TOptional<int32> Month,const TOptional<int32> Day);
            FSubscribeDailyTransactionHistoriesWithInitialCallTask(const FSubscribeDailyTransactionHistoriesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeDailyTransactionHistoriesWithInitialCallTask>> SubscribeDailyTransactionHistoriesWithInitialCall(
            TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const int32 Year,const TOptional<int32> Month = TOptional<int32>(),const TOptional<int32> Day = TOptional<int32>()
        );
        void UnsubscribeDailyTransactionHistories(
            const int32 Year
            , Gs2::Core::Domain::CallbackID CallbackID, const TOptional<int32> Month = TOptional<int32>(), const TOptional<int32> Day = TOptional<int32>()
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FDailyTransactionHistoryDomain> DailyTransactionHistory(
            const int32 Year,
            const int32 Month,
            const int32 Day,
            const FString Currency
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain> CurrentModelMaster(
        );

        Gs2::Money2::Domain::Iterator::FDescribeStoreContentModelsIteratorPtr StoreContentModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStoreContentModels(
            TFunction<void()> Callback

        );

        class FCollectStoreContentModelsTask;

        Gs2::Core::Domain::CallbackID SubscribeStoreContentModels(
            TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelPtr>)> Callback
        );

        void InvalidateStoreContentModels();

        class GS2MONEY2_API FSubscribeStoreContentModelsWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeStoreContentModelsWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelPtr>)> Callback;

        public:
            FSubscribeStoreContentModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelPtr>)> Callback);
            FSubscribeStoreContentModelsWithInitialCallTask(const FSubscribeStoreContentModelsWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeStoreContentModelsWithInitialCallTask>> SubscribeStoreContentModelsWithInitialCall(
            TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelPtr>)> Callback
        );
        void UnsubscribeStoreContentModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelDomain> StoreContentModel(
            const FString ContentName
        );

        Gs2::Money2::Domain::Iterator::FDescribeUnusedBalancesIteratorPtr UnusedBalances(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeUnusedBalances(
            TFunction<void()> Callback

        );

        class FCollectUnusedBalancesTask;

        Gs2::Core::Domain::CallbackID SubscribeUnusedBalances(
            TFunction<void(TArray<Gs2::Money2::Model::FUnusedBalancePtr>)> Callback
        );

        void InvalidateUnusedBalances();

        class GS2MONEY2_API FSubscribeUnusedBalancesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeUnusedBalancesWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Money2::Model::FUnusedBalancePtr>)> Callback;

        public:
            FSubscribeUnusedBalancesWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FUnusedBalancePtr>)> Callback);
            FSubscribeUnusedBalancesWithInitialCallTask(const FSubscribeUnusedBalancesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeUnusedBalancesWithInitialCallTask>> SubscribeUnusedBalancesWithInitialCall(
            TFunction<void(TArray<Gs2::Money2::Model::FUnusedBalancePtr>)> Callback
        );
        void UnsubscribeUnusedBalances(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FUnusedBalanceDomain> UnusedBalance(
            const FString Currency
        );

        Gs2::Money2::Domain::Iterator::FDescribeStoreContentModelMastersIteratorPtr StoreContentModelMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStoreContentModelMasters(
            TFunction<void()> Callback

        );

        class FCollectStoreContentModelMastersTask;

        Gs2::Core::Domain::CallbackID SubscribeStoreContentModelMasters(
            TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateStoreContentModelMasters(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2MONEY2_API FSubscribeStoreContentModelMastersWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeStoreContentModelMastersWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeStoreContentModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeStoreContentModelMastersWithInitialCallTask(const FSubscribeStoreContentModelMastersWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeStoreContentModelMastersWithInitialCallTask>> SubscribeStoreContentModelMastersWithInitialCall(
            TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeStoreContentModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain> StoreContentModelMaster(
            const FString ContentName
        );

        Gs2::Money2::Domain::Iterator::FDescribeStoreSubscriptionContentModelsIteratorPtr StoreSubscriptionContentModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStoreSubscriptionContentModels(
            TFunction<void()> Callback

        );

        class FCollectStoreSubscriptionContentModelsTask;

        Gs2::Core::Domain::CallbackID SubscribeStoreSubscriptionContentModels(
            TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>)> Callback
        );

        void InvalidateStoreSubscriptionContentModels();

        class GS2MONEY2_API FSubscribeStoreSubscriptionContentModelsWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeStoreSubscriptionContentModelsWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>)> Callback;

        public:
            FSubscribeStoreSubscriptionContentModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>)> Callback);
            FSubscribeStoreSubscriptionContentModelsWithInitialCallTask(const FSubscribeStoreSubscriptionContentModelsWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeStoreSubscriptionContentModelsWithInitialCallTask>> SubscribeStoreSubscriptionContentModelsWithInitialCall(
            TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>)> Callback
        );
        void UnsubscribeStoreSubscriptionContentModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelDomain> StoreSubscriptionContentModel(
            const FString ContentName
        );

        Gs2::Money2::Domain::Iterator::FDescribeStoreSubscriptionContentModelMastersIteratorPtr StoreSubscriptionContentModelMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStoreSubscriptionContentModelMasters(
            TFunction<void()> Callback

        );

        class FCollectStoreSubscriptionContentModelMastersTask;

        Gs2::Core::Domain::CallbackID SubscribeStoreSubscriptionContentModelMasters(
            TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateStoreSubscriptionContentModelMasters(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2MONEY2_API FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask(const FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask>> SubscribeStoreSubscriptionContentModelMastersWithInitialCall(
            TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeStoreSubscriptionContentModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain> StoreSubscriptionContentModelMaster(
            const FString ContentName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2MONEY2_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Model::FNamespace>,
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
                TSharedPtr<TSharedPtr<Gs2::Money2::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        void Invalidate();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Money2::Model::FNamespacePtr)> Callback
        );

        class GS2MONEY2_API FSubscribeWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(Gs2::Money2::Model::FNamespacePtr)> Callback;
        public:
            FSubscribeWithInitialCallTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                TFunction<void(Gs2::Money2::Model::FNamespacePtr)> Callback
            );

            FSubscribeWithInitialCallTask(
                const FSubscribeWithInitialCallTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeWithInitialCallTask>> SubscribeWithInitialCall(
            TFunction<void(Gs2::Money2::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
