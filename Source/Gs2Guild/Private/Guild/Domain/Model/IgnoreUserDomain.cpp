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

#include "Guild/Domain/Model/IgnoreUser.h"
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
#include "Guild/Model/Cache/IgnoreUser.h"
#include "Guild/Model/Cache/Guild.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FIgnoreUserDomain::FIgnoreUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GuildModelName,
        const TOptional<FString> GuildName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        GuildName(GuildName),
        ParentKey(Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
            NamespaceName,
            GuildModelName,
            GuildName,
            "IgnoreUser"
        ))
    {
    }

    FIgnoreUserDomain::FIgnoreUserDomain(
        const FIgnoreUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GuildModelName(From.GuildModelName),
        GuildName(From.GuildName),
        ParentKey(From.ParentKey)
    {

    }

    FIgnoreUserDomain::FGetTask::FGetTask(
        const TSharedPtr<FIgnoreUserDomain>& Self,
        const Request::FGetIgnoreUserByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIgnoreUserDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIgnoreUserDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FIgnoreUser>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->GetIgnoreUserByGuildName(
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


        Gs2::Guild::Model::Cache::FIgnoreUserCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            Request->GetGuildName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIgnoreUserDomain::FGetTask>> FIgnoreUserDomain::Get(
        Request::FGetIgnoreUserByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FIgnoreUserDomain::FAddTask::FAddTask(
        const TSharedPtr<FIgnoreUserDomain>& Self,
        const Request::FAddIgnoreUserByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIgnoreUserDomain::FAddTask::FAddTask(
        const FAddTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIgnoreUserDomain::FAddTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FIgnoreUserDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->AddIgnoreUserByGuildName(
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


        Gs2::Guild::Model::Cache::FIgnoreUserCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            Request->GetGuildName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetGuild() != nullptr)
            {


        Gs2::Guild::Model::Cache::FGuildCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            Request->GetGuildName(),
            TOptional<int32>(),
            ResultModel->GetGuild()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIgnoreUserDomain::FAddTask>> FIgnoreUserDomain::Add(
        Request::FAddIgnoreUserByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddTask>>(this->AsShared(), Request);
    }

    FIgnoreUserDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FIgnoreUserDomain>& Self,
        const Request::FDeleteIgnoreUserByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIgnoreUserDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIgnoreUserDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FIgnoreUserDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->DeleteIgnoreUserByGuildName(
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


              Gs2::Guild::Model::Cache::FIgnoreUserCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            Request->GetGuildName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIgnoreUserDomain::FDeleteTask>> FIgnoreUserDomain::Delete(
        Request::FDeleteIgnoreUserByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FIgnoreUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> GuildModelName,
        TOptional<FString> GuildName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" +
            (GuildName.IsSet() ? *GuildName : "null") + ":" +
            ChildType;
    }

    FString FIgnoreUserDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FIgnoreUserDomain::FModelTask::FModelTask(
        const TSharedPtr<FIgnoreUserDomain> Self
    ): Self(Self)
    {

    }

    FIgnoreUserDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIgnoreUserDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FIgnoreUser>> Result
    )
    {
        const auto CacheParentKey = Gs2::Guild::Model::Cache::FIgnoreUserCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->GuildModelName,
            Self->GuildName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Guild::Model::Cache::FIgnoreUserCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Guild::Model::FIgnoreUser::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Guild::Model::FIgnoreUserPtr Value;
                const auto CacheHit = Gs2::Guild::Model::Cache::FIgnoreUserCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->GuildModelName,
                    Self->GuildName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Guild::Model::Cache::FIgnoreUserCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->GuildModelName,
                    Self->GuildName,
                    TOptional<int32>(),
                    [Self](Gs2::Guild::Model::FIgnoreUserPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Guild::Request::FGetIgnoreUserByGuildNameRequest>()
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

    TSharedPtr<FAsyncTask<FIgnoreUserDomain::FModelTask>> FIgnoreUserDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FIgnoreUserDomain::FModelTask>>(this->AsShared());
    }

    void FIgnoreUserDomain::Invalidate()
    {
        Gs2::Guild::Model::Cache::FIgnoreUserCache::Delete(
            Gs2->Cache,

            NamespaceName,
            GuildModelName,
            GuildName,
            TOptional<int32>()
        );
    }

    FIgnoreUserDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FIgnoreUserDomain>& Self,
        TFunction<void(Gs2::Guild::Model::FIgnoreUserPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FIgnoreUserDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIgnoreUserDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FIgnoreUserDomain::FSubscribeWithInitialCallTask>> FIgnoreUserDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Guild::Model::FIgnoreUserPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FIgnoreUserDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FIgnoreUserPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Guild::Model::Cache::FIgnoreUserCache::CreateCacheParentKey(

            NamespaceName,
            GuildModelName,
            GuildName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Guild::Model::Cache::FIgnoreUserCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryGuildModelName = GuildModelName;
        const TOptional<FString> QueryGuildName = GuildName;
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FIgnoreUser::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FIgnoreUser>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryGuildModelName, QueryGuildName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FIgnoreUserDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryGuildModelName,
                    QueryGuildName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FIgnoreUserDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Guild::Model::Cache::FIgnoreUserCache::CreateCacheParentKey(

            NamespaceName,
            GuildModelName,
            GuildName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Guild::Model::Cache::FIgnoreUserCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FIgnoreUser::TypeName,
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
