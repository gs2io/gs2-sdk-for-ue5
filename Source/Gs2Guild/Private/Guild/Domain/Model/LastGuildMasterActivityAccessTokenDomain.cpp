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

#include "Guild/Domain/Model/LastGuildMasterActivityAccessToken.h"
#include "Guild/Domain/Model/LastGuildMasterActivity.h"
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/GuildModelMaster.h"
#include "Guild/Domain/Model/GuildModel.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/GuildAccessToken.h"
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Domain/Model/LastGuildMasterActivity.h"
#include "Guild/Domain/Model/LastGuildMasterActivityAccessToken.h"
#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/ReceiveMemberRequestAccessToken.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Domain/Model/IgnoreUser.h"
#include "Guild/Domain/Model/IgnoreUserAccessToken.h"
#include "Guild/Model/Cache/LastGuildMasterActivity.h"
#include "Guild/Model/Cache/Guild.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FLastGuildMasterActivityAccessTokenDomain::FLastGuildMasterActivityAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GuildModelName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
            NamespaceName,
            GuildModelName,
            AccessToken->GetUserId(),
            "LastGuildMasterActivity"
        ))
    {
    }

    FLastGuildMasterActivityAccessTokenDomain::FLastGuildMasterActivityAccessTokenDomain(
        const FLastGuildMasterActivityAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GuildModelName(From.GuildModelName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FLastGuildMasterActivityAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FLastGuildMasterActivityAccessTokenDomain>& Self,
        const Request::FGetLastGuildMasterActivityRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLastGuildMasterActivityAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLastGuildMasterActivityAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->GetLastGuildMasterActivity(
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
            TOptional<FString>(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetGuild() != nullptr)
            {


        Gs2::Guild::Model::Cache::FGuildCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            ResultModel->GetGuild()->GetName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetGuild()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLastGuildMasterActivityAccessTokenDomain::FGetTask>> FLastGuildMasterActivityAccessTokenDomain::Get(
        Request::FGetLastGuildMasterActivityRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FLastGuildMasterActivityAccessTokenDomain::CreateCacheParentKey(
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

    FString FLastGuildMasterActivityAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FLastGuildMasterActivityAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FLastGuildMasterActivityAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FLastGuildMasterActivityAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLastGuildMasterActivityAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity>> Result
    )
    {
        const auto CacheParentKey = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->GuildModelName,
            Self->AccessToken.IsValid() ? Self->GuildName() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
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
                    Self->AccessToken.IsValid() ? Self->GuildName() : TOptional<FString>(),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
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
                    Self->AccessToken.IsValid() ? Self->GuildName() : TOptional<FString>(),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self](Gs2::Guild::Model::FLastGuildMasterActivityPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Guild::Request::FGetLastGuildMasterActivityRequest>()
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

    TSharedPtr<FAsyncTask<FLastGuildMasterActivityAccessTokenDomain::FModelTask>> FLastGuildMasterActivityAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLastGuildMasterActivityAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FLastGuildMasterActivityAccessTokenDomain::Invalidate()
    {
        Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::Delete(
            Gs2->Cache,

            NamespaceName,
            GuildModelName,
            AccessToken.IsValid() ? GuildName() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FLastGuildMasterActivityAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FLastGuildMasterActivityAccessTokenDomain>& Self,
        TFunction<void(Gs2::Guild::Model::FLastGuildMasterActivityPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FLastGuildMasterActivityAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLastGuildMasterActivityAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FLastGuildMasterActivityAccessTokenDomain::FSubscribeWithInitialCallTask>> FLastGuildMasterActivityAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Guild::Model::FLastGuildMasterActivityPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FLastGuildMasterActivityAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FLastGuildMasterActivityPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::CreateCacheParentKey(

            NamespaceName,
            GuildModelName,
            AccessToken.IsValid() ? GuildName() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryGuildModelName = GuildModelName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FLastGuildMasterActivity::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FLastGuildMasterActivity>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryGuildModelName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FLastGuildMasterActivityAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryGuildModelName,
                    TokenSnapshot
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FLastGuildMasterActivityAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Guild::Model::Cache::FLastGuildMasterActivityCache::CreateCacheParentKey(

            NamespaceName,
            GuildModelName,
            AccessToken.IsValid() ? GuildName() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
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
