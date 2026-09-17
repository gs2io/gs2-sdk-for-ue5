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

#include "Guild/Domain/Model/LastGuildMasterActivity.h"
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
#include "Guild/Model/Cache/LastGuildMasterActivity.h"
#include "Guild/Model/Cache/Guild.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FLastGuildMasterActivityDomain::FLastGuildMasterActivityDomain(
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
            "LastGuildMasterActivity"
        ))
    {
    }

    FLastGuildMasterActivityDomain::FLastGuildMasterActivityDomain(
        const FLastGuildMasterActivityDomain& From
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

    FLastGuildMasterActivityDomain::FGetTask::FGetTask(
        const TSharedPtr<FLastGuildMasterActivityDomain>& Self,
        const Request::FGetLastGuildMasterActivityByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLastGuildMasterActivityDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLastGuildMasterActivityDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->GetLastGuildMasterActivityByGuildName(
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


        Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::Put(
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
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLastGuildMasterActivityDomain::FGetTask>> FLastGuildMasterActivityDomain::Get(
        Request::FGetLastGuildMasterActivityByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FLastGuildMasterActivityDomain::FPromoteSeniorMemberTask::FPromoteSeniorMemberTask(
        const TSharedPtr<FLastGuildMasterActivityDomain>& Self,
        const Request::FPromoteSeniorMemberByGuildNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLastGuildMasterActivityDomain::FPromoteSeniorMemberTask::FPromoteSeniorMemberTask(
        const FPromoteSeniorMemberTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLastGuildMasterActivityDomain::FPromoteSeniorMemberTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FLastGuildMasterActivityDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithGuildName(Self->GuildName);
        const auto Future = Self->Client->PromoteSeniorMemberByGuildName(
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


        Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::Put(
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

    TSharedPtr<FAsyncTask<FLastGuildMasterActivityDomain::FPromoteSeniorMemberTask>> FLastGuildMasterActivityDomain::PromoteSeniorMember(
        Request::FPromoteSeniorMemberByGuildNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPromoteSeniorMemberTask>>(this->AsShared(), Request);
    }

    FString FLastGuildMasterActivityDomain::CreateCacheParentKey(
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

    FString FLastGuildMasterActivityDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FLastGuildMasterActivityDomain::FModelTask::FModelTask(
        const TSharedPtr<FLastGuildMasterActivityDomain> Self
    ): Self(Self)
    {

    }

    FLastGuildMasterActivityDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLastGuildMasterActivityDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity>> Result
    )
    {
        const auto CacheParentKey = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->GuildModelName,
            Self->GuildName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Guild::Model::FLastGuildMasterActivity::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Guild::Model::FLastGuildMasterActivityPtr Value;
                const auto CacheHit = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::TryGet(
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
                const auto Error = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->GuildModelName,
                    Self->GuildName,
                    TOptional<int32>(),
                    [Self](Gs2::Guild::Model::FLastGuildMasterActivityPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Guild::Request::FGetLastGuildMasterActivityByGuildNameRequest>()
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

    TSharedPtr<FAsyncTask<FLastGuildMasterActivityDomain::FModelTask>> FLastGuildMasterActivityDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLastGuildMasterActivityDomain::FModelTask>>(this->AsShared());
    }

    void FLastGuildMasterActivityDomain::Invalidate()
    {
        Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::Delete(
            Gs2->Cache,

            NamespaceName,
            GuildModelName,
            GuildName,
            TOptional<int32>()
        );
    }

    FLastGuildMasterActivityDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FLastGuildMasterActivityDomain>& Self,
        TFunction<void(Gs2::Guild::Model::FLastGuildMasterActivityPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FLastGuildMasterActivityDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLastGuildMasterActivityDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FLastGuildMasterActivityDomain::FSubscribeWithInitialCallTask>> FLastGuildMasterActivityDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Guild::Model::FLastGuildMasterActivityPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FLastGuildMasterActivityDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FLastGuildMasterActivityPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::CreateCacheParentKey(

            NamespaceName,
            GuildModelName,
            GuildName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryGuildModelName = GuildModelName;
        const TOptional<FString> QueryGuildName = GuildName;
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FLastGuildMasterActivity::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryGuildModelName, QueryGuildName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FLastGuildMasterActivityDomain>(
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

    void FLastGuildMasterActivityDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::CreateCacheParentKey(

            NamespaceName,
            GuildModelName,
            GuildName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FLastGuildMasterActivity::TypeName,
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
