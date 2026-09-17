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

#include "Guild/Domain/Model/ReceiveMemberRequestAccessToken.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
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
#include "Guild/Model/Cache/SendMemberRequest.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/ReceiveMemberRequestAccessToken.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Domain/Model/IgnoreUser.h"
#include "Guild/Domain/Model/IgnoreUserAccessToken.h"
#include "Guild/Model/Cache/ReceiveMemberRequest.h"
#include "Guild/Model/Cache/Guild.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FReceiveMemberRequestAccessTokenDomain::FReceiveMemberRequestAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GuildModelName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> FromUserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        AccessToken(AccessToken),
        FromUserId(FromUserId),
        ParentKey(Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
            NamespaceName,
            GuildModelName,
            AccessToken->GetUserId(),
            "ReceiveMemberRequest"
        ))
    {
    }

    FReceiveMemberRequestAccessTokenDomain::FReceiveMemberRequestAccessTokenDomain(
        const FReceiveMemberRequestAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GuildModelName(From.GuildModelName),
        AccessToken(From.AccessToken),
        FromUserId(From.FromUserId),
        ParentKey(From.ParentKey)
    {

    }

    FReceiveMemberRequestAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FReceiveMemberRequestAccessTokenDomain>& Self,
        const Request::FGetReceiveRequestRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveMemberRequestAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveMemberRequestAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithFromUserId(Self->FromUserId);
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->GetReceiveRequest(
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


        Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            TOptional<FString>(),
            Request->GetFromUserId(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FGetTask>> FReceiveMemberRequestAccessTokenDomain::Get(
        Request::FGetReceiveRequestRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FReceiveMemberRequestAccessTokenDomain::FAcceptTask::FAcceptTask(
        const TSharedPtr<FReceiveMemberRequestAccessTokenDomain>& Self,
        const Request::FAcceptRequestRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveMemberRequestAccessTokenDomain::FAcceptTask::FAcceptTask(
        const FAcceptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveMemberRequestAccessTokenDomain::FAcceptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithFromUserId(Self->FromUserId);
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->AcceptRequest(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


        if (ResultModel.IsValid() && ResultModel->GetItem().IsValid())
        {
            Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::Delete(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                Request->GetGuildModelName(),
                ResultModel->GetItem()->GetTargetGuildName(),
                Request->GetFromUserId(),
                CacheOwnerSnapshotTimeOffset
            );
            Gs2::Guild::Model::Cache::FSendMemberRequestCache::Delete(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                ResultModel->GetItem()->GetUserId(),
                Request->GetGuildModelName(),
                ResultModel->GetItem()->GetTargetGuildName(),
                CacheOwnerSnapshotTimeOffset
            );
            if (ResultModel->GetGuild().IsValid())
            {
                Gs2::Guild::Model::Cache::FGuildCache::Delete(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(),
                    Request->GetGuildModelName(),
                    ResultModel->GetGuild()->GetName(),
                    CacheOwnerSnapshotTimeOffset
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FAcceptTask>> FReceiveMemberRequestAccessTokenDomain::Accept(
        Request::FAcceptRequestRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptTask>>(this->AsShared(), Request);
    }

    FReceiveMemberRequestAccessTokenDomain::FRejectTask::FRejectTask(
        const TSharedPtr<FReceiveMemberRequestAccessTokenDomain>& Self,
        const Request::FRejectRequestRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveMemberRequestAccessTokenDomain::FRejectTask::FRejectTask(
        const FRejectTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveMemberRequestAccessTokenDomain::FRejectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGuildModelName(Self->GuildModelName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithFromUserId(Self->FromUserId);
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->RejectRequest(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


        if (ResultModel.IsValid() && ResultModel->GetItem().IsValid())
        {
            Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::Delete(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                Request->GetGuildModelName(),
                ResultModel->GetItem()->GetTargetGuildName(),
                Request->GetFromUserId(),
                CacheOwnerSnapshotTimeOffset
            );
            Gs2::Guild::Model::Cache::FSendMemberRequestCache::Delete(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                ResultModel->GetItem()->GetUserId(),
                Request->GetGuildModelName(),
                ResultModel->GetItem()->GetTargetGuildName(),
                CacheOwnerSnapshotTimeOffset
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FRejectTask>> FReceiveMemberRequestAccessTokenDomain::Reject(
        Request::FRejectRequestRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRejectTask>>(this->AsShared(), Request);
    }

    FString FReceiveMemberRequestAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> GuildModelName,
        TOptional<FString> GuildName,
        TOptional<FString> FromUserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" +
            (GuildName.IsSet() ? *GuildName : "null") + ":" +
            (FromUserId.IsSet() ? *FromUserId : "null") + ":" +
            ChildType;
    }

    FString FReceiveMemberRequestAccessTokenDomain::CreateCacheKey(
        TOptional<FString> FromUserId
    )
    {
        return FString("") +
            (FromUserId.IsSet() ? *FromUserId : "null");
    }

    FReceiveMemberRequestAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FReceiveMemberRequestAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FReceiveMemberRequestAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveMemberRequestAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest>> Result
    )
    {
        const auto CacheParentKey = Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->GuildModelName,
            Self->AccessToken.IsValid() ? Self->GuildName() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheKey(

            Self->FromUserId
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Guild::Model::FReceiveMemberRequestPtr Value;
                const auto CacheHit = Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->GuildModelName,
                    Self->AccessToken.IsValid() ? Self->GuildName() : TOptional<FString>(),
                    Self->FromUserId,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->GuildModelName,
                    Self->AccessToken.IsValid() ? Self->GuildName() : TOptional<FString>(),
                    Self->FromUserId,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self](Gs2::Guild::Model::FReceiveMemberRequestPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Guild::Request::FGetReceiveRequestRequest>()
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

    TSharedPtr<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FModelTask>> FReceiveMemberRequestAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FReceiveMemberRequestAccessTokenDomain::Invalidate()
    {
        Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::Delete(
            Gs2->Cache,

            NamespaceName,
            GuildModelName,
            AccessToken.IsValid() ? GuildName() : TOptional<FString>(),
            FromUserId,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FReceiveMemberRequestAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FReceiveMemberRequestAccessTokenDomain>& Self,
        TFunction<void(Gs2::Guild::Model::FReceiveMemberRequestPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FReceiveMemberRequestAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveMemberRequestAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FReceiveMemberRequestAccessTokenDomain::FSubscribeWithInitialCallTask>> FReceiveMemberRequestAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Guild::Model::FReceiveMemberRequestPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FReceiveMemberRequestAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FReceiveMemberRequestPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheParentKey(

            NamespaceName,
            GuildModelName,
            AccessToken.IsValid() ? GuildName() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheKey(

            FromUserId
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryGuildModelName = GuildModelName;
        const TOptional<FString> QueryFromUserId = FromUserId;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryGuildModelName, QueryFromUserId, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FReceiveMemberRequestAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryGuildModelName,
                    TokenSnapshot,
                    QueryFromUserId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FReceiveMemberRequestAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheParentKey(

            NamespaceName,
            GuildModelName,
            AccessToken.IsValid() ? GuildName() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheKey(

            FromUserId
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
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
