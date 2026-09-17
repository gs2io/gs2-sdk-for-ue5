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

#include "MegaField/Domain/Model/LayerModelMaster.h"
#include "MegaField/Domain/Model/Namespace.h"
#include "MegaField/Domain/Model/AreaModel.h"
#include "MegaField/Domain/Model/AreaModelMaster.h"
#include "MegaField/Domain/Model/LayerModel.h"
#include "MegaField/Domain/Model/LayerModelMaster.h"
#include "MegaField/Domain/Model/CurrentFieldMaster.h"
#include "MegaField/Domain/Model/User.h"
#include "MegaField/Domain/Model/UserAccessToken.h"
#include "MegaField/Domain/Model/Spatial.h"
#include "MegaField/Domain/Model/SpatialAccessToken.h"
#include "MegaField/Model/Cache/LayerModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::MegaField::Domain::Model
{

    FLayerModelMasterDomain::FLayerModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const MegaField::Domain::FGs2MegaFieldDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> AreaModelName,
        const TOptional<FString> LayerModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::MegaField::FGs2MegaFieldRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AreaModelName(AreaModelName),
        LayerModelName(LayerModelName),
        ParentKey(Gs2::MegaField::Domain::Model::FAreaModelMasterDomain::CreateCacheParentKey(
            NamespaceName,
            AreaModelName,
            "LayerModelMaster"
        ))
    {
    }

    FLayerModelMasterDomain::FLayerModelMasterDomain(
        const FLayerModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AreaModelName(From.AreaModelName),
        LayerModelName(From.LayerModelName),
        ParentKey(From.ParentKey)
    {

    }

    FLayerModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FLayerModelMasterDomain>& Self,
        const Request::FGetLayerModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLayerModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FLayerModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->GetLayerModelMaster(
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


        Gs2::MegaField::Model::Cache::FLayerModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetAreaModelName(),
            Request->GetLayerModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLayerModelMasterDomain::FGetTask>> FLayerModelMasterDomain::Get(
        Request::FGetLayerModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FLayerModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FLayerModelMasterDomain>& Self,
        const Request::FUpdateLayerModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLayerModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->UpdateLayerModelMaster(
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


        Gs2::MegaField::Model::Cache::FLayerModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetAreaModelName(),
            Request->GetLayerModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLayerModelMasterDomain::FUpdateTask>> FLayerModelMasterDomain::Update(
        Request::FUpdateLayerModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FLayerModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FLayerModelMasterDomain>& Self,
        const Request::FDeleteLayerModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLayerModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->DeleteLayerModelMaster(
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


              Gs2::MegaField::Model::Cache::FLayerModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetAreaModelName(),
            Request->GetLayerModelName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLayerModelMasterDomain::FDeleteTask>> FLayerModelMasterDomain::Delete(
        Request::FDeleteLayerModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FLayerModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> AreaModelName,
        TOptional<FString> LayerModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" +
            (LayerModelName.IsSet() ? *LayerModelName : "null") + ":" +
            ChildType;
    }

    FString FLayerModelMasterDomain::CreateCacheKey(
        TOptional<FString> LayerModelName
    )
    {
        return FString("") +
            (LayerModelName.IsSet() ? *LayerModelName : "null");
    }

    FLayerModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FLayerModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FLayerModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FLayerModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::MegaField::Model::Cache::FLayerModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AreaModelName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::MegaField::Model::Cache::FLayerModelMasterCache::CreateCacheKey(

            Self->LayerModelName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::MegaField::Model::FLayerModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::MegaField::Model::FLayerModelMasterPtr Value;
                const auto CacheHit = Gs2::MegaField::Model::Cache::FLayerModelMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AreaModelName,
                    Self->LayerModelName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::MegaField::Model::Cache::FLayerModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AreaModelName,
                    Self->LayerModelName,
                    TOptional<int32>(),
                    [Self](Gs2::MegaField::Model::FLayerModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::MegaField::Request::FGetLayerModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FLayerModelMasterDomain::FModelTask>> FLayerModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLayerModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FLayerModelMasterDomain::Invalidate()
    {
        Gs2::MegaField::Model::Cache::FLayerModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AreaModelName,
            LayerModelName,
            TOptional<int32>()
        );
    }

    FLayerModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FLayerModelMasterDomain>& Self,
        TFunction<void(Gs2::MegaField::Model::FLayerModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FLayerModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLayerModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FLayerModelMasterDomain::FSubscribeWithInitialCallTask>> FLayerModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::MegaField::Model::FLayerModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FLayerModelMasterDomain::Subscribe(
        TFunction<void(Gs2::MegaField::Model::FLayerModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::MegaField::Model::Cache::FLayerModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            AreaModelName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::MegaField::Model::Cache::FLayerModelMasterCache::CreateCacheKey(

            LayerModelName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<MegaField::Domain::FGs2MegaFieldDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryAreaModelName = AreaModelName;
        const TOptional<FString> QueryLayerModelName = LayerModelName;
        return Gs2->Cache->Subscribe(
            Gs2::MegaField::Model::FLayerModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::MegaField::Model::FLayerModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryAreaModelName, QueryLayerModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FLayerModelMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryAreaModelName,
                    QueryLayerModelName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FLayerModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::MegaField::Model::Cache::FLayerModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            AreaModelName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::MegaField::Model::Cache::FLayerModelMasterCache::CreateCacheKey(

            LayerModelName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::MegaField::Model::FLayerModelMaster::TypeName,
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
