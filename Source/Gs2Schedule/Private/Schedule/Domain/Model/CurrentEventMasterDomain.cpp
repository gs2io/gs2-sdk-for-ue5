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

#include "Schedule/Domain/Model/CurrentEventMaster.h"
#include "Schedule/Domain/Model/Namespace.h"
#include "Schedule/Domain/Model/EventMaster.h"
#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Domain/Model/TriggerAccessToken.h"
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Domain/Model/EventAccessToken.h"
#include "Schedule/Domain/Model/User.h"
#include "Schedule/Domain/Model/UserAccessToken.h"
#include "Schedule/Domain/Model/CurrentEventMaster.h"
#include "Schedule/Model/Cache/CurrentEventMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Schedule::Domain::Model
{

    FCurrentEventMasterDomain::FCurrentEventMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Schedule::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentEventMaster"
        ))
    {
    }

    FCurrentEventMasterDomain::FCurrentEventMasterDomain(
        const FCurrentEventMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FCurrentEventMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentEventMasterDomain>& Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentEventMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEventMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FCurrentEventMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->ExportMaster(
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


        Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::Put(
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

    TSharedPtr<FAsyncTask<FCurrentEventMasterDomain::FExportMasterTask>> FCurrentEventMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentEventMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentEventMasterDomain>& Self,
        const Request::FGetCurrentEventMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentEventMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEventMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FCurrentEventMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentEventMaster(
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


        Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentEventMasterDomain::FGetTask>> FCurrentEventMasterDomain::Get(
        Request::FGetCurrentEventMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentEventMasterDomain::FPreUpdateTask::FPreUpdateTask(
        const TSharedPtr<FCurrentEventMasterDomain>& Self,
        const Request::FPreUpdateCurrentEventMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentEventMasterDomain::FPreUpdateTask::FPreUpdateTask(
        const FPreUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEventMasterDomain::FPreUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FCurrentEventMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->PreUpdateCurrentEventMaster(
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
            if (ResultModel->GetUploadToken().IsSet())
            {
                Self->UploadToken = Domain->UploadToken = ResultModel->GetUploadToken();
            }
            if (ResultModel->GetUploadUrl().IsSet())
            {
                Self->UploadUrl = Domain->UploadUrl = ResultModel->GetUploadUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentEventMasterDomain::FPreUpdateTask>> FCurrentEventMasterDomain::PreUpdate(
        Request::FPreUpdateCurrentEventMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPreUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentEventMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentEventMasterDomain>& Self,
        const Request::FUpdateCurrentEventMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentEventMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEventMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FCurrentEventMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentEventMaster(
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


        Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::Put(
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

    TSharedPtr<FAsyncTask<FCurrentEventMasterDomain::FUpdateTask>> FCurrentEventMasterDomain::Update(
        Request::FUpdateCurrentEventMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentEventMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentEventMasterDomain>& Self,
        const Request::FUpdateCurrentEventMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentEventMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEventMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FCurrentEventMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentEventMasterFromGitHub(
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


        Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::Put(
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

    TSharedPtr<FAsyncTask<FCurrentEventMasterDomain::FUpdateFromGitHubTask>> FCurrentEventMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentEventMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentEventMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentEventMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentEventMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentEventMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentEventMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEventMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FCurrentEventMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Schedule::Model::FCurrentEventMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Schedule::Model::FCurrentEventMasterPtr Value;
                const auto CacheHit = Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::TryGet(
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
                const auto Error = Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    TOptional<int32>(),
                    [Self](Gs2::Schedule::Model::FCurrentEventMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Schedule::Request::FGetCurrentEventMasterRequest>()
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

    TSharedPtr<FAsyncTask<FCurrentEventMasterDomain::FModelTask>> FCurrentEventMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentEventMasterDomain::FModelTask>>(this->AsShared());
    }

    void FCurrentEventMasterDomain::Invalidate()
    {
        Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            TOptional<int32>()
        );
    }

    FCurrentEventMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FCurrentEventMasterDomain>& Self,
        TFunction<void(Gs2::Schedule::Model::FCurrentEventMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FCurrentEventMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentEventMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FCurrentEventMasterDomain::FSubscribeWithInitialCallTask>> FCurrentEventMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Schedule::Model::FCurrentEventMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FCurrentEventMasterDomain::Subscribe(
        TFunction<void(Gs2::Schedule::Model::FCurrentEventMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Schedule::Domain::FGs2ScheduleDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        return Gs2->Cache->Subscribe(
            Gs2::Schedule::Model::FCurrentEventMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Schedule::Model::FCurrentEventMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FCurrentEventMasterDomain>(
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

    void FCurrentEventMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Schedule::Model::Cache::FCurrentEventMasterCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Schedule::Model::FCurrentEventMaster::TypeName,
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
