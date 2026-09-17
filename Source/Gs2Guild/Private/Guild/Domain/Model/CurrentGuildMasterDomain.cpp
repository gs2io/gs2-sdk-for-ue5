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

#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/GuildModelMaster.h"
#include "Guild/Domain/Model/GuildModel.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Domain/Model/LastGuildMasterActivity.h"
#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Domain/Model/IgnoreUser.h"
#include "Guild/Model/Cache/CurrentGuildMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FCurrentGuildMasterDomain::FCurrentGuildMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentGuildMaster"
        ))
    {
    }

    FCurrentGuildMasterDomain::FCurrentGuildMasterDomain(
        const FCurrentGuildMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FCurrentGuildMasterDomain::FExportMasterTask::FExportMasterTask(
        const TSharedPtr<FCurrentGuildMasterDomain>& Self,
        const Request::FExportMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentGuildMasterDomain::FExportMasterTask::FExportMasterTask(
        const FExportMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FExportMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain>> Result
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


        Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::Put(
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

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FExportMasterTask>> FCurrentGuildMasterDomain::ExportMaster(
        Request::FExportMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FExportMasterTask>>(this->AsShared(), Request);
    }

    FCurrentGuildMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCurrentGuildMasterDomain>& Self,
        const Request::FGetCurrentGuildMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentGuildMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FCurrentGuildMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetCurrentGuildMaster(
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


        Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FGetTask>> FCurrentGuildMasterDomain::Get(
        Request::FGetCurrentGuildMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCurrentGuildMasterDomain::FPreUpdateTask::FPreUpdateTask(
        const TSharedPtr<FCurrentGuildMasterDomain>& Self,
        const Request::FPreUpdateCurrentGuildMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentGuildMasterDomain::FPreUpdateTask::FPreUpdateTask(
        const FPreUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FPreUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->PreUpdateCurrentGuildMaster(
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

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FPreUpdateTask>> FCurrentGuildMasterDomain::PreUpdate(
        Request::FPreUpdateCurrentGuildMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPreUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentGuildMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentGuildMasterDomain>& Self,
        const Request::FUpdateCurrentGuildMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentGuildMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentGuildMaster(
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


        Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::Put(
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

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FUpdateTask>> FCurrentGuildMasterDomain::Update(
        Request::FUpdateCurrentGuildMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentGuildMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FCurrentGuildMasterDomain>& Self,
        const Request::FUpdateCurrentGuildMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentGuildMasterDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentGuildMasterFromGitHub(
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


        Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::Put(
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

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FUpdateFromGitHubTask>> FCurrentGuildMasterDomain::UpdateFromGitHub(
        Request::FUpdateCurrentGuildMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentGuildMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentGuildMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FCurrentGuildMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCurrentGuildMasterDomain> Self
    ): Self(Self)
    {

    }

    FCurrentGuildMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FCurrentGuildMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Guild::Model::FCurrentGuildMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Guild::Model::FCurrentGuildMasterPtr Value;
                const auto CacheHit = Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::TryGet(
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
                const auto Error = Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    TOptional<int32>(),
                    [Self](Gs2::Guild::Model::FCurrentGuildMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Guild::Request::FGetCurrentGuildMasterRequest>()
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

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FModelTask>> FCurrentGuildMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCurrentGuildMasterDomain::FModelTask>>(this->AsShared());
    }

    void FCurrentGuildMasterDomain::Invalidate()
    {
        Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            TOptional<int32>()
        );
    }

    FCurrentGuildMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FCurrentGuildMasterDomain>& Self,
        TFunction<void(Gs2::Guild::Model::FCurrentGuildMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FCurrentGuildMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentGuildMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FCurrentGuildMasterDomain::FSubscribeWithInitialCallTask>> FCurrentGuildMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Guild::Model::FCurrentGuildMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FCurrentGuildMasterDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FCurrentGuildMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FCurrentGuildMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FCurrentGuildMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FCurrentGuildMasterDomain>(
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

    void FCurrentGuildMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Guild::Model::Cache::FCurrentGuildMasterCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FCurrentGuildMaster::TypeName,
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
