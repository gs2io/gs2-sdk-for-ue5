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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Money2/Domain/Model/Namespace.h"
#include "Money2/Domain/Model/Namespace.h"
#include "Money2/Domain/Model/User.h"
#include "Money2/Domain/Model/UserAccessToken.h"
#include "Money2/Domain/Model/Wallet.h"
#include "Money2/Domain/Model/WalletAccessToken.h"
#include "Money2/Domain/Model/Event.h"
#include "Money2/Domain/Model/EventAccessToken.h"
#include "Money2/Domain/Model/SubscriptionStatus.h"
#include "Money2/Domain/Model/SubscriptionStatusAccessToken.h"
#include "Money2/Domain/Model/RefundHistory.h"
#include "Money2/Domain/Model/StoreContentModel.h"
#include "Money2/Domain/Model/StoreContentModelMaster.h"
#include "Money2/Domain/Model/StoreSubscriptionContentModel.h"
#include "Money2/Domain/Model/StoreSubscriptionContentModelMaster.h"
#include "Money2/Domain/Model/CurrentModelMaster.h"
#include "Money2/Domain/Model/DailyTransactionHistory.h"
#include "Money2/Domain/Model/UnusedBalance.h"
#include "Money2/Model/Cache/Namespace.h"
#include "Money2/Model/Cache/StoreContentModelMaster.h"
#include "Money2/Model/Cache/StoreSubscriptionContentModelMaster.h"
#include "Money2/Model/Cache/DailyTransactionHistory.h"
#include "Money2/Model/Cache/Wallet.h"
#include "Money2/Model/Cache/Event.h"
#include "Money2/Model/Cache/SubscriptionStatus.h"
#include "Money2/Model/Cache/CurrentModelMaster.h"
#include "Money2/Model/Cache/StoreContentModel.h"
#include "Money2/Model/Cache/UnusedBalance.h"
#include "Money2/Model/Cache/StoreSubscriptionContentModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Money2::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("money2:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespaceStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetStatus().IsSet())
            {
                Self->Status = Domain->Status = ResultModel->GetStatus();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FNamespace>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Money2::Model::Cache::FNamespaceCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Money2::Model::Cache::FNamespaceCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FUpdateTask>> FNamespaceDomain::Update(
        Request::FUpdateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDeleteNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


              Gs2::Money2::Model::Cache::FNamespaceCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateStoreContentModelMasterTask::FCreateStoreContentModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateStoreContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateStoreContentModelMasterTask::FCreateStoreContentModelMasterTask(
        const FCreateStoreContentModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateStoreContentModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateStoreContentModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Money2::Model::Cache::FStoreContentModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateStoreContentModelMasterTask>> FNamespaceDomain::CreateStoreContentModelMaster(
        Request::FCreateStoreContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateStoreContentModelMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateStoreSubscriptionContentModelMasterTask::FCreateStoreSubscriptionContentModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateStoreSubscriptionContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateStoreSubscriptionContentModelMasterTask::FCreateStoreSubscriptionContentModelMasterTask(
        const FCreateStoreSubscriptionContentModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateStoreSubscriptionContentModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateStoreSubscriptionContentModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateStoreSubscriptionContentModelMasterTask>> FNamespaceDomain::CreateStoreSubscriptionContentModelMaster(
        Request::FCreateStoreSubscriptionContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateStoreSubscriptionContentModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::Money2::Domain::Iterator::FDescribeDailyTransactionHistoriesByCurrencyIteratorPtr FNamespaceDomain::DailyTransactionHistoriesByCurrency(
        const FString Currency,
        const int32 Year,
        const TOptional<int32> Month
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeDailyTransactionHistoriesByCurrencyIterator>(
            Gs2,
            Client,
            NamespaceName,
            Currency,
            Year,
            Month
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDailyTransactionHistoriesByCurrency(
    TFunction<void()> Callback
        , const int32 Year, const TOptional<int32> Month
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeDailyTransactionHistoriesByCurrency(
        const int32 Year
        , Gs2::Core::Domain::CallbackID CallbackID, const FString Currency, const TOptional<int32> Month
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectDailyTransactionHistoriesByCurrencyTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>>, public TSharedFromThis<FCollectDailyTransactionHistoriesByCurrencyTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> OnCollected;
    const FString QueryCurrency;const int32 QueryYear;const TOptional<int32> QueryMonth;
    public:
        explicit FCollectDailyTransactionHistoriesByCurrencyTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> OnCollected,const FString Currency,const int32 Year,const TOptional<int32> Month) : Self(Self), OnCollected(OnCollected), QueryCurrency(Currency), QueryYear(Year), QueryMonth(Month) {}
        FCollectDailyTransactionHistoriesByCurrencyTask(const FCollectDailyTransactionHistoriesByCurrencyTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryCurrency(From.QueryCurrency), QueryYear(From.QueryYear), QueryMonth(From.QueryMonth) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>>> Result) override
        {
            TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr> Items;
            auto Iterator = Self->DailyTransactionHistoriesByCurrency(QueryCurrency, QueryYear, QueryMonth)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDailyTransactionHistoriesByCurrency(
        TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const FString Currency,const int32 Year,const TOptional<int32> Month
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryCurrency = Currency;
        const auto QueryYear = Year;
        const auto QueryMonth = Month;
        const auto Parent = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryCurrency, QueryYear, QueryMonth]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDailyTransactionHistoriesByCurrencyTask>>(Domain, Callback, QueryCurrency, QueryYear, QueryMonth);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateDailyTransactionHistoriesByCurrency(const FString Currency,const int32 Year,const TOptional<int32> Month)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask::FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const FString Currency,const int32 Year,const TOptional<int32> Month) : Self(Self), Callback(Callback), QueryCurrency(Currency), QueryYear(Year), QueryMonth(Month) {}
    FNamespaceDomain::FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask::FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask(const FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryCurrency(From.QueryCurrency), QueryYear(From.QueryYear), QueryMonth(From.QueryMonth) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDailyTransactionHistoriesByCurrencyTask>>(Self, TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)>(), QueryCurrency, QueryYear, QueryMonth);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeDailyTransactionHistoriesByCurrency(Callback, QueryCurrency, QueryYear, QueryMonth);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask>> FNamespaceDomain::SubscribeDailyTransactionHistoriesByCurrencyWithInitialCall(TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const FString Currency,const int32 Year,const TOptional<int32> Month)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeDailyTransactionHistoriesByCurrencyWithInitialCallTask>>(this->AsShared(), Callback, Currency, Year, Month);
    }

    Gs2::Money2::Domain::Iterator::FDescribeDailyTransactionHistoriesIteratorPtr FNamespaceDomain::DailyTransactionHistories(
        const int32 Year,
        const TOptional<int32> Month,
        const TOptional<int32> Day
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeDailyTransactionHistoriesIterator>(
            Gs2,
            Client,
            NamespaceName,
            Year,
            Month,
            Day
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDailyTransactionHistories(
    TFunction<void()> Callback
        , const int32 Year, const TOptional<int32> Month, const TOptional<int32> Day
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeDailyTransactionHistories(
        const int32 Year
        , Gs2::Core::Domain::CallbackID CallbackID, const TOptional<int32> Month, const TOptional<int32> Day
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectDailyTransactionHistoriesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>>, public TSharedFromThis<FCollectDailyTransactionHistoriesTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> OnCollected;
    const int32 QueryYear;const TOptional<int32> QueryMonth;const TOptional<int32> QueryDay;
    public:
        explicit FCollectDailyTransactionHistoriesTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> OnCollected,const int32 Year,const TOptional<int32> Month,const TOptional<int32> Day) : Self(Self), OnCollected(OnCollected), QueryYear(Year), QueryMonth(Month), QueryDay(Day) {}
        FCollectDailyTransactionHistoriesTask(const FCollectDailyTransactionHistoriesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryYear(From.QueryYear), QueryMonth(From.QueryMonth), QueryDay(From.QueryDay) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>>> Result) override
        {
            TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr> Items;
            auto Iterator = Self->DailyTransactionHistories(QueryYear, QueryMonth, QueryDay)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDailyTransactionHistories(
        TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const int32 Year,const TOptional<int32> Month,const TOptional<int32> Day
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryYear = Year;
        const auto QueryMonth = Month;
        const auto QueryDay = Day;
        const auto Parent = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryYear, QueryMonth, QueryDay]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDailyTransactionHistoriesTask>>(Domain, Callback, QueryYear, QueryMonth, QueryDay);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateDailyTransactionHistories(const int32 Year,const TOptional<int32> Month,const TOptional<int32> Day)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeDailyTransactionHistoriesWithInitialCallTask::FSubscribeDailyTransactionHistoriesWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const int32 Year,const TOptional<int32> Month,const TOptional<int32> Day) : Self(Self), Callback(Callback), QueryYear(Year), QueryMonth(Month), QueryDay(Day) {}
    FNamespaceDomain::FSubscribeDailyTransactionHistoriesWithInitialCallTask::FSubscribeDailyTransactionHistoriesWithInitialCallTask(const FSubscribeDailyTransactionHistoriesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryYear(From.QueryYear), QueryMonth(From.QueryMonth), QueryDay(From.QueryDay) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeDailyTransactionHistoriesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDailyTransactionHistoriesTask>>(Self, TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)>(), QueryYear, QueryMonth, QueryDay);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeDailyTransactionHistories(Callback, QueryYear, QueryMonth, QueryDay);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeDailyTransactionHistoriesWithInitialCallTask>> FNamespaceDomain::SubscribeDailyTransactionHistoriesWithInitialCall(TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> Callback,const int32 Year,const TOptional<int32> Month,const TOptional<int32> Day)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeDailyTransactionHistoriesWithInitialCallTask>>(this->AsShared(), Callback, Year, Month, Day);
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FDailyTransactionHistoryDomain> FNamespaceDomain::DailyTransactionHistory(
        const int32 Year,
        const int32 Month,
        const int32 Day,
        const FString Currency
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FDailyTransactionHistoryDomain>(
            Gs2,
            Service,
            NamespaceName,
            Year,
            Month,
            Day,
            Currency == TEXT("") ? TOptional<FString>() : TOptional<FString>(Currency)
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain> FNamespaceDomain::CurrentModelMaster(
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FCurrentModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeStoreContentModelsIteratorPtr FNamespaceDomain::StoreContentModels(
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeStoreContentModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreContentModels(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FStoreContentModel::TypeName,
            Gs2::Money2::Model::Cache::FStoreContentModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeStoreContentModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FStoreContentModel::TypeName,
            Gs2::Money2::Model::Cache::FStoreContentModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectStoreContentModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money2::Model::FStoreContentModelPtr>>, public TSharedFromThis<FCollectStoreContentModelsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelPtr>)> OnCollected;

    public:
        explicit FCollectStoreContentModelsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectStoreContentModelsTask(const FCollectStoreContentModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money2::Model::FStoreContentModelPtr>>> Result) override
        {
            TArray<Gs2::Money2::Model::FStoreContentModelPtr> Items;
            auto Iterator = Self->StoreContentModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money2::Model::FStoreContentModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreContentModels(
        TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Money2::Model::Cache::FStoreContentModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money2::Model::FStoreContentModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money2::Model::FStoreContentModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FStoreContentModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStoreContentModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateStoreContentModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money2::Model::FStoreContentModel::TypeName,
            Gs2::Money2::Model::Cache::FStoreContentModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeStoreContentModelsWithInitialCallTask::FSubscribeStoreContentModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeStoreContentModelsWithInitialCallTask::FSubscribeStoreContentModelsWithInitialCallTask(const FSubscribeStoreContentModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeStoreContentModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStoreContentModelsTask>>(Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeStoreContentModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeStoreContentModelsWithInitialCallTask>> FNamespaceDomain::SubscribeStoreContentModelsWithInitialCall(TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeStoreContentModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelDomain> FNamespaceDomain::StoreContentModel(
        const FString ContentName
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FStoreContentModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            ContentName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ContentName)
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeUnusedBalancesIteratorPtr FNamespaceDomain::UnusedBalances(
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeUnusedBalancesIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeUnusedBalances(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FUnusedBalance::TypeName,
            Gs2::Money2::Model::Cache::FUnusedBalanceCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeUnusedBalances(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FUnusedBalance::TypeName,
            Gs2::Money2::Model::Cache::FUnusedBalanceCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectUnusedBalancesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money2::Model::FUnusedBalancePtr>>, public TSharedFromThis<FCollectUnusedBalancesTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Money2::Model::FUnusedBalancePtr>)> OnCollected;

    public:
        explicit FCollectUnusedBalancesTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FUnusedBalancePtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectUnusedBalancesTask(const FCollectUnusedBalancesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money2::Model::FUnusedBalancePtr>>> Result) override
        {
            TArray<Gs2::Money2::Model::FUnusedBalancePtr> Items;
            auto Iterator = Self->UnusedBalances()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money2::Model::FUnusedBalancePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeUnusedBalances(
        TFunction<void(TArray<Gs2::Money2::Model::FUnusedBalancePtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Money2::Model::Cache::FUnusedBalanceCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money2::Model::FUnusedBalance::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money2::Model::FUnusedBalancePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FUnusedBalance>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectUnusedBalancesTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateUnusedBalances()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money2::Model::FUnusedBalance::TypeName,
            Gs2::Money2::Model::Cache::FUnusedBalanceCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeUnusedBalancesWithInitialCallTask::FSubscribeUnusedBalancesWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FUnusedBalancePtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeUnusedBalancesWithInitialCallTask::FSubscribeUnusedBalancesWithInitialCallTask(const FSubscribeUnusedBalancesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeUnusedBalancesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectUnusedBalancesTask>>(Self, TFunction<void(TArray<Gs2::Money2::Model::FUnusedBalancePtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeUnusedBalances(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeUnusedBalancesWithInitialCallTask>> FNamespaceDomain::SubscribeUnusedBalancesWithInitialCall(TFunction<void(TArray<Gs2::Money2::Model::FUnusedBalancePtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeUnusedBalancesWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FUnusedBalanceDomain> FNamespaceDomain::UnusedBalance(
        const FString Currency
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FUnusedBalanceDomain>(
            Gs2,
            Service,
            NamespaceName,
            Currency == TEXT("") ? TOptional<FString>() : TOptional<FString>(Currency)
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeStoreContentModelMastersIteratorPtr FNamespaceDomain::StoreContentModelMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeStoreContentModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreContentModelMasters(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
            Gs2::Money2::Model::Cache::FStoreContentModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeStoreContentModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
            Gs2::Money2::Model::Cache::FStoreContentModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectStoreContentModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>>, public TSharedFromThis<FCollectStoreContentModelMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectStoreContentModelMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectStoreContentModelMastersTask(const FCollectStoreContentModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr> Items;
            auto Iterator = Self->StoreContentModelMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreContentModelMasters(
        TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Money2::Model::Cache::FStoreContentModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FStoreContentModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStoreContentModelMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateStoreContentModelMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money2::Model::FStoreContentModelMaster::TypeName,
            Gs2::Money2::Model::Cache::FStoreContentModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeStoreContentModelMastersWithInitialCallTask::FSubscribeStoreContentModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeStoreContentModelMastersWithInitialCallTask::FSubscribeStoreContentModelMastersWithInitialCallTask(const FSubscribeStoreContentModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeStoreContentModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStoreContentModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeStoreContentModelMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeStoreContentModelMastersWithInitialCallTask>> FNamespaceDomain::SubscribeStoreContentModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Money2::Model::FStoreContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeStoreContentModelMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain> FNamespaceDomain::StoreContentModelMaster(
        const FString ContentName
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FStoreContentModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            ContentName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ContentName)
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeStoreSubscriptionContentModelsIteratorPtr FNamespaceDomain::StoreSubscriptionContentModels(
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeStoreSubscriptionContentModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreSubscriptionContentModels(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModel::TypeName,
            Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeStoreSubscriptionContentModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModel::TypeName,
            Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectStoreSubscriptionContentModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>>, public TSharedFromThis<FCollectStoreSubscriptionContentModelsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>)> OnCollected;

    public:
        explicit FCollectStoreSubscriptionContentModelsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectStoreSubscriptionContentModelsTask(const FCollectStoreSubscriptionContentModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>>> Result) override
        {
            TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr> Items;
            auto Iterator = Self->StoreSubscriptionContentModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreSubscriptionContentModels(
        TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money2::Model::FStoreSubscriptionContentModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FStoreSubscriptionContentModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStoreSubscriptionContentModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateStoreSubscriptionContentModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money2::Model::FStoreSubscriptionContentModel::TypeName,
            Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeStoreSubscriptionContentModelsWithInitialCallTask::FSubscribeStoreSubscriptionContentModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeStoreSubscriptionContentModelsWithInitialCallTask::FSubscribeStoreSubscriptionContentModelsWithInitialCallTask(const FSubscribeStoreSubscriptionContentModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeStoreSubscriptionContentModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStoreSubscriptionContentModelsTask>>(Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeStoreSubscriptionContentModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeStoreSubscriptionContentModelsWithInitialCallTask>> FNamespaceDomain::SubscribeStoreSubscriptionContentModelsWithInitialCall(TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeStoreSubscriptionContentModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelDomain> FNamespaceDomain::StoreSubscriptionContentModel(
        const FString ContentName
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            ContentName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ContentName)
        );
    }

    Gs2::Money2::Domain::Iterator::FDescribeStoreSubscriptionContentModelMastersIteratorPtr FNamespaceDomain::StoreSubscriptionContentModelMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Money2::Domain::Iterator::FDescribeStoreSubscriptionContentModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreSubscriptionContentModelMasters(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
            Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeStoreSubscriptionContentModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
            Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectStoreSubscriptionContentModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>>, public TSharedFromThis<FCollectStoreSubscriptionContentModelMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectStoreSubscriptionContentModelMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectStoreSubscriptionContentModelMastersTask(const FCollectStoreSubscriptionContentModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr> Items;
            auto Iterator = Self->StoreSubscriptionContentModelMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStoreSubscriptionContentModelMasters(
        TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FStoreSubscriptionContentModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStoreSubscriptionContentModelMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateStoreSubscriptionContentModelMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
            Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask::FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask::FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask(const FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStoreSubscriptionContentModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeStoreSubscriptionContentModelMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask>> FNamespaceDomain::SubscribeStoreSubscriptionContentModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeStoreSubscriptionContentModelMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain> FNamespaceDomain::StoreSubscriptionContentModelMaster(
        const FString ContentName
    )
    {
        return MakeShared<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            ContentName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ContentName)
        );
    }

    FString FNamespaceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FNamespaceDomain::CreateCacheKey(
        TOptional<FString> NamespaceName
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null");
    }

    FNamespaceDomain::FModelTask::FModelTask(
        const TSharedPtr<FNamespaceDomain> Self
    ): Self(Self)
    {

    }

    FNamespaceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FNamespace>> Result
    )
    {
        const auto CacheParentKey = Gs2::Money2::Model::Cache::FNamespaceCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Money2::Model::Cache::FNamespaceCache::CreateCacheKey(

            Self->NamespaceName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Money2::Model::FNamespace::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Money2::Model::FNamespacePtr Value;
                const auto CacheHit = Gs2::Money2::Model::Cache::FNamespaceCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Money2::Model::Cache::FNamespaceCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    TOptional<int32>(),
                    [Self](Gs2::Money2::Model::FNamespacePtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Money2::Request::FGetNamespaceRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }

    void FNamespaceDomain::Invalidate()
    {
        Gs2::Money2::Model::Cache::FNamespaceCache::Delete(
            Gs2->Cache,

            NamespaceName,
            TOptional<int32>()
        );
    }

    FNamespaceDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        TFunction<void(Gs2::Money2::Model::FNamespacePtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FNamespaceDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeWithInitialCallTask>> FNamespaceDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Money2::Model::FNamespacePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FNamespacePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Money2::Model::Cache::FNamespaceCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Money2::Model::Cache::FNamespaceCache::CreateCacheKey(

            NamespaceName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FNamespace::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FNamespace>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FNamespaceDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Money2::Model::Cache::FNamespaceCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Money2::Model::Cache::FNamespaceCache::CreateCacheKey(

            NamespaceName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FNamespace::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
