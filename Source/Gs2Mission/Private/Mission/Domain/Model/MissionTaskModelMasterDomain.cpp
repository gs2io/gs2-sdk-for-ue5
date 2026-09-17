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

#include "Mission/Domain/Model/MissionTaskModelMaster.h"
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Domain/Model/CompleteAccessToken.h"
#include "Mission/Domain/Model/CounterModelMaster.h"
#include "Mission/Domain/Model/MissionGroupModelMaster.h"
#include "Mission/Domain/Model/Namespace.h"
#include "Mission/Domain/Model/Counter.h"
#include "Mission/Domain/Model/CounterAccessToken.h"
#include "Mission/Domain/Model/CurrentMissionMaster.h"
#include "Mission/Domain/Model/CounterModel.h"
#include "Mission/Domain/Model/MissionGroupModel.h"
#include "Mission/Domain/Model/MissionTaskModel.h"
#include "Mission/Domain/Model/MissionTaskModelMaster.h"
#include "Mission/Domain/Model/User.h"
#include "Mission/Domain/Model/UserAccessToken.h"
#include "Mission/Model/Cache/MissionTaskModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Mission::Domain::Model
{

    FMissionTaskModelMasterDomain::FMissionTaskModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Mission::Domain::FGs2MissionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> MissionGroupName,
        const TOptional<FString> MissionTaskName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        MissionGroupName(MissionGroupName),
        MissionTaskName(MissionTaskName),
        ParentKey(Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheParentKey(
            NamespaceName,
            MissionGroupName,
            "MissionTaskModelMaster"
        ))
    {
    }

    FMissionTaskModelMasterDomain::FMissionTaskModelMasterDomain(
        const FMissionTaskModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        MissionGroupName(From.MissionGroupName),
        MissionTaskName(From.MissionTaskName),
        ParentKey(From.ParentKey)
    {

    }

    FMissionTaskModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FMissionTaskModelMasterDomain>& Self,
        const Request::FGetMissionTaskModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionTaskModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionTaskModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithMissionTaskName(Self->MissionTaskName);
        const auto Future = Self->Client->GetMissionTaskModelMaster(
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


        Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMissionGroupName(),
            Request->GetMissionTaskName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionTaskModelMasterDomain::FGetTask>> FMissionTaskModelMasterDomain::Get(
        Request::FGetMissionTaskModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMissionTaskModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FMissionTaskModelMasterDomain>& Self,
        const Request::FUpdateMissionTaskModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionTaskModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithMissionTaskName(Self->MissionTaskName);
        const auto Future = Self->Client->UpdateMissionTaskModelMaster(
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


        Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMissionGroupName(),
            Request->GetMissionTaskName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionTaskModelMasterDomain::FUpdateTask>> FMissionTaskModelMasterDomain::Update(
        Request::FUpdateMissionTaskModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FMissionTaskModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMissionTaskModelMasterDomain>& Self,
        const Request::FDeleteMissionTaskModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionTaskModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithMissionTaskName(Self->MissionTaskName);
        const auto Future = Self->Client->DeleteMissionTaskModelMaster(
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


              Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMissionGroupName(),
            Request->GetMissionTaskName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionTaskModelMasterDomain::FDeleteTask>> FMissionTaskModelMasterDomain::Delete(
        Request::FDeleteMissionTaskModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FMissionTaskModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> MissionGroupName,
        TOptional<FString> MissionTaskName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null") + ":" +
            (MissionTaskName.IsSet() ? *MissionTaskName : "null") + ":" +
            ChildType;
    }

    FString FMissionTaskModelMasterDomain::CreateCacheKey(
        TOptional<FString> MissionTaskName
    )
    {
        return FString("") +
            (MissionTaskName.IsSet() ? *MissionTaskName : "null");
    }

    FMissionTaskModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FMissionTaskModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FMissionTaskModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionTaskModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->MissionGroupName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::CreateCacheKey(

            Self->MissionTaskName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Mission::Model::FMissionTaskModelMasterPtr Value;
                const auto CacheHit = Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->MissionGroupName,
                    Self->MissionTaskName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->MissionGroupName,
                    Self->MissionTaskName,
                    TOptional<int32>(),
                    [Self](Gs2::Mission::Model::FMissionTaskModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Mission::Request::FGetMissionTaskModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FMissionTaskModelMasterDomain::FModelTask>> FMissionTaskModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMissionTaskModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FMissionTaskModelMasterDomain::Invalidate()
    {
        Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            MissionGroupName,
            MissionTaskName,
            TOptional<int32>()
        );
    }

    FMissionTaskModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FMissionTaskModelMasterDomain>& Self,
        TFunction<void(Gs2::Mission::Model::FMissionTaskModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FMissionTaskModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FMissionTaskModelMasterDomain::FSubscribeWithInitialCallTask>> FMissionTaskModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Mission::Model::FMissionTaskModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FMissionTaskModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Mission::Model::FMissionTaskModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            MissionGroupName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::CreateCacheKey(

            MissionTaskName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Mission::Domain::FGs2MissionDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryMissionGroupName = MissionGroupName;
        const TOptional<FString> QueryMissionTaskName = MissionTaskName;
        return Gs2->Cache->Subscribe(
            Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Mission::Model::FMissionTaskModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryMissionGroupName, QueryMissionTaskName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FMissionTaskModelMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryMissionGroupName,
                    QueryMissionTaskName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FMissionTaskModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            MissionGroupName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::CreateCacheKey(

            MissionTaskName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
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
