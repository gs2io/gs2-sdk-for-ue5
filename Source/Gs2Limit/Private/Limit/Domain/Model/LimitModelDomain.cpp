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

#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/Namespace.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/LimitModelMaster.h"
#include "Limit/Domain/Model/CurrentLimitMaster.h"
#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/User.h"
#include "Limit/Domain/Model/UserAccessToken.h"
#include "Limit/Model/Cache/LimitModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Limit::Domain::Model
{

    FLimitModelDomain::FLimitModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Limit::Domain::FGs2LimitDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> LimitName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Limit::FGs2LimitRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        LimitName(LimitName),
        ParentKey(Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "LimitModel"
        ))
    {
    }

    FLimitModelDomain::FLimitModelDomain(
        const FLimitModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        LimitName(From.LimitName),
        ParentKey(From.ParentKey)
    {

    }

    FLimitModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FLimitModelDomain>& Self,
        const Request::FGetLimitModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLimitModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLimitModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FLimitModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLimitName(Self->LimitName);
        const auto Future = Self->Client->GetLimitModel(
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


        Gs2::Limit::Model::Cache::FLimitModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetLimitName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLimitModelDomain::FGetTask>> FLimitModelDomain::Get(
        Request::FGetLimitModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FLimitModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> LimitName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (LimitName.IsSet() ? *LimitName : "null") + ":" +
            ChildType;
    }

    FString FLimitModelDomain::CreateCacheKey(
        TOptional<FString> LimitName
    )
    {
        return FString("") +
            (LimitName.IsSet() ? *LimitName : "null");
    }

    FLimitModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FLimitModelDomain> Self
    ): Self(Self)
    {

    }

    FLimitModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLimitModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FLimitModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Limit::Model::Cache::FLimitModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Limit::Model::Cache::FLimitModelCache::CreateCacheKey(

            Self->LimitName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Limit::Model::FLimitModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Limit::Model::FLimitModelPtr Value;
                const auto CacheHit = Gs2::Limit::Model::Cache::FLimitModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->LimitName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Limit::Model::Cache::FLimitModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->LimitName,
                    TOptional<int32>(),
                    [Self](Gs2::Limit::Model::FLimitModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Limit::Request::FGetLimitModelRequest>()
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

    TSharedPtr<FAsyncTask<FLimitModelDomain::FModelTask>> FLimitModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLimitModelDomain::FModelTask>>(this->AsShared());
    }

    void FLimitModelDomain::Invalidate()
    {
        Gs2::Limit::Model::Cache::FLimitModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            LimitName,
            TOptional<int32>()
        );
    }

    FLimitModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FLimitModelDomain>& Self,
        TFunction<void(Gs2::Limit::Model::FLimitModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FLimitModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLimitModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FLimitModelDomain::FSubscribeWithInitialCallTask>> FLimitModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Limit::Model::FLimitModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FLimitModelDomain::Subscribe(
        TFunction<void(Gs2::Limit::Model::FLimitModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Limit::Model::Cache::FLimitModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Limit::Model::Cache::FLimitModelCache::CreateCacheKey(

            LimitName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Limit::Domain::FGs2LimitDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryLimitName = LimitName;
        return Gs2->Cache->Subscribe(
            Gs2::Limit::Model::FLimitModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Limit::Model::FLimitModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryLimitName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FLimitModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryLimitName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FLimitModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Limit::Model::Cache::FLimitModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Limit::Model::Cache::FLimitModelCache::CreateCacheKey(

            LimitName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Limit::Model::FLimitModel::TypeName,
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
