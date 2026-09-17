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

#include "Lottery/Domain/Model/PrizeLimit.h"
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
#include "Lottery/Model/Cache/PrizeLimit.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FPrizeLimitDomain::FPrizeLimitDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> PrizeTableName,
        const TOptional<FString> PrizeId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        PrizeTableName(PrizeTableName),
        PrizeId(PrizeId),
        ParentKey(Gs2::Lottery::Domain::Model::FPrizeTableDomain::CreateCacheParentKey(
            NamespaceName,
            PrizeTableName,
            "PrizeLimit"
        ))
    {
    }

    FPrizeLimitDomain::FPrizeLimitDomain(
        const FPrizeLimitDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        PrizeTableName(From.PrizeTableName),
        PrizeId(From.PrizeId),
        ParentKey(From.ParentKey)
    {

    }

    FPrizeLimitDomain::FGetTask::FGetTask(
        const TSharedPtr<FPrizeLimitDomain>& Self,
        const Request::FGetPrizeLimitRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPrizeLimitDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeLimitDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeLimit>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName)
            ->WithPrizeId(Self->PrizeId);
        const auto Future = Self->Client->GetPrizeLimit(
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
        Gs2::Lottery::Model::Cache::FPrizeLimitCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetPrizeTableName(),
            ResultModel->GetItem()->GetPrizeId(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPrizeLimitDomain::FGetTask>> FPrizeLimitDomain::Get(
        Request::FGetPrizeLimitRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPrizeLimitDomain::FResetTask::FResetTask(
        const TSharedPtr<FPrizeLimitDomain>& Self,
        const Request::FResetPrizeLimitRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPrizeLimitDomain::FResetTask::FResetTask(
        const FResetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeLimitDomain::FResetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeLimitDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName)
            ->WithPrizeId(Self->PrizeId);
        const auto Future = Self->Client->ResetPrizeLimit(
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
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPrizeLimitDomain::FResetTask>> FPrizeLimitDomain::Reset(
        Request::FResetPrizeLimitRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FResetTask>>(this->AsShared(), Request);
    }

    FString FPrizeLimitDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> PrizeTableName,
        TOptional<FString> PrizeId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null") + ":" +
            (PrizeId.IsSet() ? *PrizeId : "null") + ":" +
            ChildType;
    }

    FString FPrizeLimitDomain::CreateCacheKey(
        TOptional<FString> PrizeId
    )
    {
        return FString("") +
            (PrizeId.IsSet() ? *PrizeId : "null");
    }

    FPrizeLimitDomain::FModelTask::FModelTask(
        const TSharedPtr<FPrizeLimitDomain> Self
    ): Self(Self)
    {

    }

    FPrizeLimitDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeLimitDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeLimit>> Result
    )
    {
        const auto CacheParentKey = Gs2::Lottery::Model::Cache::FPrizeLimitCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->PrizeTableName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Lottery::Model::Cache::FPrizeLimitCache::CreateCacheKey(

            Self->PrizeId
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Lottery::Model::FPrizeLimit::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Lottery::Model::FPrizeLimitPtr Value;
                const auto CacheHit = Gs2::Lottery::Model::Cache::FPrizeLimitCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->PrizeTableName,
                    Self->PrizeId,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Lottery::Model::Cache::FPrizeLimitCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->PrizeTableName,
                    Self->PrizeId,
                    TOptional<int32>(),
                    [Self](Gs2::Lottery::Model::FPrizeLimitPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Lottery::Request::FGetPrizeLimitRequest>()
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

    TSharedPtr<FAsyncTask<FPrizeLimitDomain::FModelTask>> FPrizeLimitDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPrizeLimitDomain::FModelTask>>(this->AsShared());
    }

    void FPrizeLimitDomain::Invalidate()
    {
        Gs2::Lottery::Model::Cache::FPrizeLimitCache::Delete(
            Gs2->Cache,

            NamespaceName,
            PrizeTableName,
            PrizeId,
            TOptional<int32>()
        );
    }

    FPrizeLimitDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FPrizeLimitDomain>& Self,
        TFunction<void(Gs2::Lottery::Model::FPrizeLimitPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FPrizeLimitDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeLimitDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FPrizeLimitDomain::FSubscribeWithInitialCallTask>> FPrizeLimitDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Lottery::Model::FPrizeLimitPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FPrizeLimitDomain::Subscribe(
        TFunction<void(Gs2::Lottery::Model::FPrizeLimitPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Lottery::Model::Cache::FPrizeLimitCache::CreateCacheParentKey(

            NamespaceName,
            PrizeTableName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Lottery::Model::Cache::FPrizeLimitCache::CreateCacheKey(

            PrizeId
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Lottery::Domain::FGs2LotteryDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryPrizeTableName = PrizeTableName;
        const TOptional<FString> QueryPrizeId = PrizeId;
        return Gs2->Cache->Subscribe(
            Gs2::Lottery::Model::FPrizeLimit::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Lottery::Model::FPrizeLimit>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryPrizeTableName, QueryPrizeId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FPrizeLimitDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryPrizeTableName,
                    QueryPrizeId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FPrizeLimitDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Lottery::Model::Cache::FPrizeLimitCache::CreateCacheParentKey(

            NamespaceName,
            PrizeTableName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Lottery::Model::Cache::FPrizeLimitCache::CreateCacheKey(

            PrizeId
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Lottery::Model::FPrizeLimit::TypeName,
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
