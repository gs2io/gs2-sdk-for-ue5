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

#include "Lottery/Domain/Model/LotteryModel.h"
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
#include "Lottery/Model/Cache/LotteryModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FLotteryModelDomain::FLotteryModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> LotteryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        LotteryName(LotteryName),
        ParentKey(Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "LotteryModel"
        ))
    {
    }

    FLotteryModelDomain::FLotteryModelDomain(
        const FLotteryModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        LotteryName(From.LotteryName),
        ParentKey(From.ParentKey)
    {

    }

    FLotteryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FLotteryModelDomain>& Self,
        const Request::FGetLotteryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLotteryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FLotteryModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLotteryName(Self->LotteryName);
        const auto Future = Self->Client->GetLotteryModel(
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


        Gs2::Lottery::Model::Cache::FLotteryModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetLotteryName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLotteryModelDomain::FGetTask>> FLotteryModelDomain::Get(
        Request::FGetLotteryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FLotteryModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> LotteryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (LotteryName.IsSet() ? *LotteryName : "null") + ":" +
            ChildType;
    }

    FString FLotteryModelDomain::CreateCacheKey(
        TOptional<FString> LotteryName
    )
    {
        return FString("") +
            (LotteryName.IsSet() ? *LotteryName : "null");
    }

    FLotteryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FLotteryModelDomain> Self
    ): Self(Self)
    {

    }

    FLotteryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FLotteryModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Lottery::Model::Cache::FLotteryModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Lottery::Model::Cache::FLotteryModelCache::CreateCacheKey(

            Self->LotteryName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Lottery::Model::FLotteryModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Lottery::Model::FLotteryModelPtr Value;
                const auto CacheHit = Gs2::Lottery::Model::Cache::FLotteryModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->LotteryName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Lottery::Model::Cache::FLotteryModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->LotteryName,
                    TOptional<int32>(),
                    [Self](Gs2::Lottery::Model::FLotteryModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Lottery::Request::FGetLotteryModelRequest>()
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

    TSharedPtr<FAsyncTask<FLotteryModelDomain::FModelTask>> FLotteryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLotteryModelDomain::FModelTask>>(this->AsShared());
    }

    void FLotteryModelDomain::Invalidate()
    {
        Gs2::Lottery::Model::Cache::FLotteryModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            LotteryName,
            TOptional<int32>()
        );
    }

    FLotteryModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FLotteryModelDomain>& Self,
        TFunction<void(Gs2::Lottery::Model::FLotteryModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FLotteryModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FLotteryModelDomain::FSubscribeWithInitialCallTask>> FLotteryModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Lottery::Model::FLotteryModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FLotteryModelDomain::Subscribe(
        TFunction<void(Gs2::Lottery::Model::FLotteryModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Lottery::Model::Cache::FLotteryModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Lottery::Model::Cache::FLotteryModelCache::CreateCacheKey(

            LotteryName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Lottery::Domain::FGs2LotteryDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryLotteryName = LotteryName;
        return Gs2->Cache->Subscribe(
            Gs2::Lottery::Model::FLotteryModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Lottery::Model::FLotteryModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryLotteryName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FLotteryModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryLotteryName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FLotteryModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Lottery::Model::Cache::FLotteryModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Lottery::Model::Cache::FLotteryModelCache::CreateCacheKey(

            LotteryName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Lottery::Model::FLotteryModel::TypeName,
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
