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

#include "Lottery/Domain/Model/PrizeTable.h"
#include "Lottery/Domain/Model/Namespace.h"
#include "Lottery/Domain/Model/LotteryModelMaster.h"
#include "Lottery/Domain/Model/PrizeTableMaster.h"
#include "Lottery/Domain/Model/LotteryModel.h"
#include "Lottery/Domain/Model/PrizeTable.h"
#include "Lottery/Domain/Model/Lottery.h"
#include "Lottery/Domain/Model/LotteryAccessToken.h"
#include "Lottery/Domain/Model/Probability.h"
#include "Lottery/Domain/Model/ProbabilityAccessToken.h"
#include "Lottery/Domain/Model/CurrentLotteryMaster.h"
#include "Lottery/Domain/Model/PrizeLimit.h"
#include "Lottery/Domain/Model/BoxItems.h"
#include "Lottery/Domain/Model/BoxItemsAccessToken.h"
#include "Lottery/Domain/Model/User.h"
#include "Lottery/Domain/Model/UserAccessToken.h"
#include "Lottery/Model/Cache/PrizeTable.h"
#include "Lottery/Model/Cache/PrizeLimit.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FPrizeTableDomain::FPrizeTableDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> PrizeTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        PrizeTableName(PrizeTableName),
        ParentKey(Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "PrizeTable"
        ))
    {
    }

    FPrizeTableDomain::FPrizeTableDomain(
        const FPrizeTableDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        PrizeTableName(From.PrizeTableName),
        ParentKey(From.ParentKey)
    {

    }

    FPrizeTableDomain::FGetTask::FGetTask(
        const TSharedPtr<FPrizeTableDomain>& Self,
        const Request::FGetPrizeTableRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPrizeTableDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeTableDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeTable>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName);
        const auto Future = Self->Client->GetPrizeTable(
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


        Gs2::Lottery::Model::Cache::FPrizeTableCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetPrizeTableName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPrizeTableDomain::FGetTask>> FPrizeTableDomain::Get(
        Request::FGetPrizeTableRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Lottery::Domain::Iterator::FDescribePrizeLimitsIteratorPtr FPrizeTableDomain::PrizeLimits(
    ) const
    {
        return MakeShared<Gs2::Lottery::Domain::Iterator::FDescribePrizeLimitsIterator>(
            Gs2,
            Client,
            NamespaceName,
            PrizeTableName
        );
    }

    Gs2::Core::Domain::CallbackID FPrizeTableDomain::SubscribePrizeLimits(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Lottery::Model::FPrizeLimit::TypeName,
            Gs2::Lottery::Model::Cache::FPrizeLimitCache::CreateCacheParentKey(
                NamespaceName,
                PrizeTableName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FPrizeTableDomain::UnsubscribePrizeLimits(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Lottery::Model::FPrizeLimit::TypeName,
            Gs2::Lottery::Model::Cache::FPrizeLimitCache::CreateCacheParentKey(
                NamespaceName,
                PrizeTableName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FPrizeTableDomain::FCollectPrizeLimitsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Lottery::Model::FPrizeLimitPtr>>, public TSharedFromThis<FCollectPrizeLimitsTask>
    {
        const TSharedPtr<FPrizeTableDomain> Self;
        const TFunction<void(TArray<Gs2::Lottery::Model::FPrizeLimitPtr>)> OnCollected;

    public:
        explicit FCollectPrizeLimitsTask(const TSharedPtr<FPrizeTableDomain>& Self, TFunction<void(TArray<Gs2::Lottery::Model::FPrizeLimitPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectPrizeLimitsTask(const FCollectPrizeLimitsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Lottery::Model::FPrizeLimitPtr>>> Result) override
        {
            TArray<Gs2::Lottery::Model::FPrizeLimitPtr> Items;
            auto Iterator = Self->PrizeLimits()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Lottery::Model::FPrizeLimitPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FPrizeTableDomain::SubscribePrizeLimits(
        TFunction<void(TArray<Gs2::Lottery::Model::FPrizeLimitPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Lottery::Domain::FGs2LotteryDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryPrizeTableName = PrizeTableName;
        const auto Parent = Gs2::Lottery::Model::Cache::FPrizeLimitCache::CreateCacheParentKey(
        NamespaceName,
        PrizeTableName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Lottery::Model::FPrizeLimit::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Lottery::Model::FPrizeLimitPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Lottery::Model::FPrizeLimit>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryPrizeTableName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FPrizeTableDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryPrizeTableName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectPrizeLimitsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FPrizeTableDomain::InvalidatePrizeLimits()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Lottery::Model::FPrizeLimit::TypeName,
            Gs2::Lottery::Model::Cache::FPrizeLimitCache::CreateCacheParentKey(
        NamespaceName,
        PrizeTableName,
        TOptional<int32>()
    )
        );
    }

    FPrizeTableDomain::FSubscribePrizeLimitsWithInitialCallTask::FSubscribePrizeLimitsWithInitialCallTask(const TSharedPtr<FPrizeTableDomain>& Self, TFunction<void(TArray<Gs2::Lottery::Model::FPrizeLimitPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FPrizeTableDomain::FSubscribePrizeLimitsWithInitialCallTask::FSubscribePrizeLimitsWithInitialCallTask(const FSubscribePrizeLimitsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FPrizeTableDomain::FSubscribePrizeLimitsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectPrizeLimitsTask>>(Self, TFunction<void(TArray<Gs2::Lottery::Model::FPrizeLimitPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribePrizeLimits(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FPrizeTableDomain::FSubscribePrizeLimitsWithInitialCallTask>> FPrizeTableDomain::SubscribePrizeLimitsWithInitialCall(TFunction<void(TArray<Gs2::Lottery::Model::FPrizeLimitPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribePrizeLimitsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeLimitDomain> FPrizeTableDomain::PrizeLimit(
        const FString PrizeId
    )
    {
        return MakeShared<Gs2::Lottery::Domain::Model::FPrizeLimitDomain>(
            Gs2,
            Service,
            NamespaceName,
            PrizeTableName,
            PrizeId == TEXT("") ? TOptional<FString>() : TOptional<FString>(PrizeId)
        );
    }

    FString FPrizeTableDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> PrizeTableName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null") + ":" +
            ChildType;
    }

    FString FPrizeTableDomain::CreateCacheKey(
        TOptional<FString> PrizeTableName
    )
    {
        return FString("") +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null");
    }

    FPrizeTableDomain::FModelTask::FModelTask(
        const TSharedPtr<FPrizeTableDomain> Self
    ): Self(Self)
    {

    }

    FPrizeTableDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeTableDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeTable>> Result
    )
    {
        const auto CacheParentKey = Gs2::Lottery::Model::Cache::FPrizeTableCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Lottery::Model::Cache::FPrizeTableCache::CreateCacheKey(

            Self->PrizeTableName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Lottery::Model::FPrizeTable::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Lottery::Model::FPrizeTablePtr Value;
                const auto CacheHit = Gs2::Lottery::Model::Cache::FPrizeTableCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->PrizeTableName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Lottery::Model::Cache::FPrizeTableCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->PrizeTableName,
                    TOptional<int32>(),
                    [Self](Gs2::Lottery::Model::FPrizeTablePtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Lottery::Request::FGetPrizeTableRequest>()
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

    TSharedPtr<FAsyncTask<FPrizeTableDomain::FModelTask>> FPrizeTableDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPrizeTableDomain::FModelTask>>(this->AsShared());
    }

    void FPrizeTableDomain::Invalidate()
    {
        Gs2::Lottery::Model::Cache::FPrizeTableCache::Delete(
            Gs2->Cache,

            NamespaceName,
            PrizeTableName,
            TOptional<int32>()
        );
    }

    FPrizeTableDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FPrizeTableDomain>& Self,
        TFunction<void(Gs2::Lottery::Model::FPrizeTablePtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FPrizeTableDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeTableDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FPrizeTableDomain::FSubscribeWithInitialCallTask>> FPrizeTableDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Lottery::Model::FPrizeTablePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FPrizeTableDomain::Subscribe(
        TFunction<void(Gs2::Lottery::Model::FPrizeTablePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Lottery::Model::Cache::FPrizeTableCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Lottery::Model::Cache::FPrizeTableCache::CreateCacheKey(

            PrizeTableName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Lottery::Domain::FGs2LotteryDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryPrizeTableName = PrizeTableName;
        return Gs2->Cache->Subscribe(
            Gs2::Lottery::Model::FPrizeTable::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Lottery::Model::FPrizeTable>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryPrizeTableName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FPrizeTableDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryPrizeTableName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FPrizeTableDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Lottery::Model::Cache::FPrizeTableCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Lottery::Model::Cache::FPrizeTableCache::CreateCacheKey(

            PrizeTableName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Lottery::Model::FPrizeTable::TypeName,
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
