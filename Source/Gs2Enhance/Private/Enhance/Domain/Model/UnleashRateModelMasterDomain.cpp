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

#include "Enhance/Domain/Model/UnleashRateModelMaster.h"
#include "Enhance/Domain/Model/Namespace.h"
#include "Enhance/Domain/Model/RateModel.h"
#include "Enhance/Domain/Model/RateModelMaster.h"
#include "Enhance/Domain/Model/UnleashRateModel.h"
#include "Enhance/Domain/Model/UnleashRateModelMaster.h"
#include "Enhance/Domain/Model/Enhance.h"
#include "Enhance/Domain/Model/EnhanceAccessToken.h"
#include "Enhance/Domain/Model/Progress.h"
#include "Enhance/Domain/Model/ProgressAccessToken.h"
#include "Enhance/Domain/Model/CurrentRateMaster.h"
#include "Enhance/Domain/Model/User.h"
#include "Enhance/Domain/Model/UserAccessToken.h"
#include "Enhance/Model/Cache/UnleashRateModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Enhance::Domain::Model
{

    FUnleashRateModelMasterDomain::FUnleashRateModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RateName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Enhance::FGs2EnhanceRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RateName(RateName),
        ParentKey(Gs2::Enhance::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "UnleashRateModelMaster"
        ))
    {
    }

    FUnleashRateModelMasterDomain::FUnleashRateModelMasterDomain(
        const FUnleashRateModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RateName(From.RateName),
        ParentKey(From.ParentKey)
    {

    }

    FUnleashRateModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FUnleashRateModelMasterDomain>& Self,
        const Request::FGetUnleashRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUnleashRateModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUnleashRateModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FUnleashRateModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->GetUnleashRateModelMaster(
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


        Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetRateName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUnleashRateModelMasterDomain::FGetTask>> FUnleashRateModelMasterDomain::Get(
        Request::FGetUnleashRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FUnleashRateModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FUnleashRateModelMasterDomain>& Self,
        const Request::FUpdateUnleashRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUnleashRateModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUnleashRateModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->UpdateUnleashRateModelMaster(
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


        Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetRateName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUnleashRateModelMasterDomain::FUpdateTask>> FUnleashRateModelMasterDomain::Update(
        Request::FUpdateUnleashRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FUnleashRateModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FUnleashRateModelMasterDomain>& Self,
        const Request::FDeleteUnleashRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUnleashRateModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUnleashRateModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->DeleteUnleashRateModelMaster(
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


              Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetRateName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUnleashRateModelMasterDomain::FDeleteTask>> FUnleashRateModelMasterDomain::Delete(
        Request::FDeleteUnleashRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FUnleashRateModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RateName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RateName.IsSet() ? *RateName : "null") + ":" +
            ChildType;
    }

    FString FUnleashRateModelMasterDomain::CreateCacheKey(
        TOptional<FString> RateName
    )
    {
        return FString("") +
            (RateName.IsSet() ? *RateName : "null");
    }

    FUnleashRateModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FUnleashRateModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FUnleashRateModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FUnleashRateModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FUnleashRateModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::CreateCacheKey(

            Self->RateName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Enhance::Model::FUnleashRateModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Enhance::Model::FUnleashRateModelMasterPtr Value;
                const auto CacheHit = Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RateName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RateName,
                    TOptional<int32>(),
                    [Self](Gs2::Enhance::Model::FUnleashRateModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Enhance::Request::FGetUnleashRateModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FUnleashRateModelMasterDomain::FModelTask>> FUnleashRateModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FUnleashRateModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FUnleashRateModelMasterDomain::Invalidate()
    {
        Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            RateName,
            TOptional<int32>()
        );
    }

    FUnleashRateModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FUnleashRateModelMasterDomain>& Self,
        TFunction<void(Gs2::Enhance::Model::FUnleashRateModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FUnleashRateModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUnleashRateModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FUnleashRateModelMasterDomain::FSubscribeWithInitialCallTask>> FUnleashRateModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Enhance::Model::FUnleashRateModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FUnleashRateModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Enhance::Model::FUnleashRateModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::CreateCacheKey(

            RateName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Enhance::Domain::FGs2EnhanceDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryRateName = RateName;
        return Gs2->Cache->Subscribe(
            Gs2::Enhance::Model::FUnleashRateModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Enhance::Model::FUnleashRateModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryRateName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FUnleashRateModelMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryRateName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FUnleashRateModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::CreateCacheKey(

            RateName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Enhance::Model::FUnleashRateModelMaster::TypeName,
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
