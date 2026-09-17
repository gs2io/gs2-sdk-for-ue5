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

#include "Buff/Domain/Model/CurrentBuffMaster.h"
#include "Buff/Domain/Model/Namespace.h"
#include "Buff/Domain/Model/BuffEntryModel.h"
#include "Buff/Domain/Model/BuffEntryModelMaster.h"
#include "Buff/Domain/Model/Buff.h"
#include "Buff/Domain/Model/BuffAccessToken.h"
#include "Buff/Domain/Model/CurrentBuffMaster.h"
#include "Buff/Domain/Model/User.h"
#include "Buff/Domain/Model/UserAccessToken.h"
#include "Buff/Model/Cache/CurrentBuffMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Buff::Domain::Model
{

    FCurrentBuffMasterDomain::FCurrentBuffMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Buff::Domain::FGs2BuffDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Buff::FGs2BuffRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Buff::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentBuffMaster"
        ))
    {
    }

    FCurrentBuffMasterDomain::FCurrentBuffMasterDomain(
        const FCurrentBuffMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FCurrentBuffMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentBuffMasterDomain>& Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentBuffMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentBuffMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain>> Result
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


        Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::Put(
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

    TSharedPtr<FAsyncTask<FCurrentBuffMasterDomain::FExportMasterTask>> FCurrentBuffMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentBuffMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentBuffMasterDomain>& Self,
        const Request::FGetCurrentBuffMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentBuffMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentBuffMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Buff::Model::FCurrentBuffMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentBuffMaster(
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


        Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentBuffMasterDomain::FGetTask>> FCurrentBuffMasterDomain::Get(
        Request::FGetCurrentBuffMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentBuffMasterDomain::FPreUpdateTask::FPreUpdateTask(
        const TSharedPtr<FCurrentBuffMasterDomain>& Self,
        const Request::FPreUpdateCurrentBuffMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentBuffMasterDomain::FPreUpdateTask::FPreUpdateTask(
        const FPreUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentBuffMasterDomain::FPreUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->PreUpdateCurrentBuffMaster(
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

    TSharedPtr<FAsyncTask<FCurrentBuffMasterDomain::FPreUpdateTask>> FCurrentBuffMasterDomain::PreUpdate(
        Request::FPreUpdateCurrentBuffMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPreUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentBuffMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentBuffMasterDomain>& Self,
        const Request::FUpdateCurrentBuffMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentBuffMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentBuffMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentBuffMaster(
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


        Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::Put(
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

    TSharedPtr<FAsyncTask<FCurrentBuffMasterDomain::FUpdateTask>> FCurrentBuffMasterDomain::Update(
        Request::FUpdateCurrentBuffMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentBuffMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentBuffMasterDomain>& Self,
        const Request::FUpdateCurrentBuffMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentBuffMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentBuffMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Buff::Domain::Model::FCurrentBuffMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentBuffMasterFromGitHub(
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


        Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::Put(
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

    TSharedPtr<FAsyncTask<FCurrentBuffMasterDomain::FUpdateFromGitHubTask>> FCurrentBuffMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentBuffMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentBuffMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentBuffMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentBuffMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentBuffMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentBuffMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentBuffMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Buff::Model::FCurrentBuffMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Buff::Model::FCurrentBuffMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Buff::Model::FCurrentBuffMasterPtr Value;
                const auto CacheHit = Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::TryGet(
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
                const auto Error = Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    TOptional<int32>(),
                    [Self](Gs2::Buff::Model::FCurrentBuffMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Buff::Request::FGetCurrentBuffMasterRequest>()
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

    TSharedPtr<FAsyncTask<FCurrentBuffMasterDomain::FModelTask>> FCurrentBuffMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentBuffMasterDomain::FModelTask>>(this->AsShared());
    }

    void FCurrentBuffMasterDomain::Invalidate()
    {
        Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            TOptional<int32>()
        );
    }

    FCurrentBuffMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FCurrentBuffMasterDomain>& Self,
        TFunction<void(Gs2::Buff::Model::FCurrentBuffMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FCurrentBuffMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentBuffMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FCurrentBuffMasterDomain::FSubscribeWithInitialCallTask>> FCurrentBuffMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Buff::Model::FCurrentBuffMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FCurrentBuffMasterDomain::Subscribe(
        TFunction<void(Gs2::Buff::Model::FCurrentBuffMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Buff::Domain::FGs2BuffDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        return Gs2->Cache->Subscribe(
            Gs2::Buff::Model::FCurrentBuffMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Buff::Model::FCurrentBuffMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FCurrentBuffMasterDomain>(
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

    void FCurrentBuffMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Buff::Model::Cache::FCurrentBuffMasterCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Buff::Model::FCurrentBuffMaster::TypeName,
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
