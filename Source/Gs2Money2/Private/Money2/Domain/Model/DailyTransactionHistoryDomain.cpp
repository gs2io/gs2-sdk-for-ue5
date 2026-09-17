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

#include "Money2/Domain/Model/DailyTransactionHistory.h"
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
#include "Money2/Model/Cache/DailyTransactionHistory.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Money2::Domain::Model
{

    FDailyTransactionHistoryDomain::FDailyTransactionHistoryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<int32> Year,
        const TOptional<int32> Month,
        const TOptional<int32> Day,
        const TOptional<FString> Currency
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Year(Year),
        Month(Month),
        Day(Day),
        Currency(Currency),
        ParentKey(Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "DailyTransactionHistory"
        ))
    {
    }

    FDailyTransactionHistoryDomain::FDailyTransactionHistoryDomain(
        const FDailyTransactionHistoryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Year(From.Year),
        Month(From.Month),
        Day(From.Day),
        Currency(From.Currency),
        ParentKey(From.ParentKey)
    {

    }

    FDailyTransactionHistoryDomain::FGetTask::FGetTask(
        const TSharedPtr<FDailyTransactionHistoryDomain>& Self,
        const Request::FGetDailyTransactionHistoryRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDailyTransactionHistoryDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDailyTransactionHistoryDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithYear(Self->Year)
            ->WithMonth(Self->Month)
            ->WithDay(Self->Day)
            ->WithCurrency(Self->Currency);
        const auto Future = Self->Client->GetDailyTransactionHistory(
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

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetYear().Get(int32{}),
            ResultModel->GetItem()->GetMonth().Get(int32{}),
            ResultModel->GetItem()->GetDay().Get(int32{}),
            ResultModel->GetItem()->GetCurrency(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDailyTransactionHistoryDomain::FGetTask>> FDailyTransactionHistoryDomain::Get(
        Request::FGetDailyTransactionHistoryRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FDailyTransactionHistoryDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<int32> Year,
        TOptional<int32> Month,
        TOptional<int32> Day,
        TOptional<FString> Currency,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Year.IsSet() ? FString::FromInt(*Year) : "null") + ":" +
            (Month.IsSet() ? FString::FromInt(*Month) : "null") + ":" +
            (Day.IsSet() ? FString::FromInt(*Day) : "null") + ":" +
            (Currency.IsSet() ? *Currency : "null") + ":" +
            ChildType;
    }

    FString FDailyTransactionHistoryDomain::CreateCacheKey(
        TOptional<int32> Year,
        TOptional<int32> Month,
        TOptional<int32> Day,
        TOptional<FString> Currency
    )
    {
        return FString("") +
            (Year.IsSet() ? FString::FromInt(*Year) : "null") + ":" +
            (Month.IsSet() ? FString::FromInt(*Month) : "null") + ":" +
            (Day.IsSet() ? FString::FromInt(*Day) : "null") + ":" +
            (Currency.IsSet() ? *Currency : "null");
    }

    FDailyTransactionHistoryDomain::FModelTask::FModelTask(
        const TSharedPtr<FDailyTransactionHistoryDomain> Self
    ): Self(Self)
    {

    }

    FDailyTransactionHistoryDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDailyTransactionHistoryDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>> Result
    )
    {
        const auto CacheParentKey = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheKey(

            Self->Year,
            Self->Month,
            Self->Day,
            Self->Currency
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Money2::Model::FDailyTransactionHistoryPtr Value;
                const auto CacheHit = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->Year,
                    Self->Month,
                    Self->Day,
                    Self->Currency,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->Year,
                    Self->Month,
                    Self->Day,
                    Self->Currency,
                    TOptional<int32>(),
                    [Self](Gs2::Money2::Model::FDailyTransactionHistoryPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Money2::Request::FGetDailyTransactionHistoryRequest>()
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

    TSharedPtr<FAsyncTask<FDailyTransactionHistoryDomain::FModelTask>> FDailyTransactionHistoryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDailyTransactionHistoryDomain::FModelTask>>(this->AsShared());
    }

    void FDailyTransactionHistoryDomain::Invalidate()
    {
        Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::Delete(
            Gs2->Cache,

            NamespaceName,
            Year,
            Month,
            Day,
            Currency,
            TOptional<int32>()
        );
    }

    FDailyTransactionHistoryDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FDailyTransactionHistoryDomain>& Self,
        TFunction<void(Gs2::Money2::Model::FDailyTransactionHistoryPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FDailyTransactionHistoryDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDailyTransactionHistoryDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FDailyTransactionHistoryDomain::FSubscribeWithInitialCallTask>> FDailyTransactionHistoryDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Money2::Model::FDailyTransactionHistoryPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FDailyTransactionHistoryDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FDailyTransactionHistoryPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheKey(

            Year,
            Month,
            Day,
            Currency
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<int32> QueryYear = Year;
        const TOptional<int32> QueryMonth = Month;
        const TOptional<int32> QueryDay = Day;
        const TOptional<FString> QueryCurrency = Currency;
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryYear, QueryMonth, QueryDay, QueryCurrency]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FDailyTransactionHistoryDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryYear,
                    QueryMonth,
                    QueryDay,
                    QueryCurrency
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FDailyTransactionHistoryDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheKey(

            Year,
            Month,
            Day,
            Currency
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
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
