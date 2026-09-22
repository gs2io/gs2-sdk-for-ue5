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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Gateway/Domain/Model/WebSocketSessionAccessToken.h"
#include "Gateway/Domain/Model/WebSocketSession.h"
#include "Gateway/Domain/Model/Namespace.h"
#include "Gateway/Domain/Model/WebSocketSession.h"
#include "Gateway/Domain/Model/WebSocketSessionAccessToken.h"
#include "Gateway/Domain/Model/FirebaseToken.h"
#include "Gateway/Domain/Model/FirebaseTokenAccessToken.h"
#include "Gateway/Domain/Model/User.h"
#include "Gateway/Domain/Model/UserAccessToken.h"
#include "Gateway/Model/Cache/WebSocketSession.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Gateway::Domain::Model
{

    FWebSocketSessionAccessTokenDomain::FWebSocketSessionAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Gateway::Domain::FGs2GatewayDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Gateway::FGs2GatewayRestClient>(Gs2->RestSession)),
        Wsclient(MakeShared<Gs2::Gateway::FGs2GatewayWebSocketClient>(Gs2->WebSocketSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken)
    {
    }

    FWebSocketSessionAccessTokenDomain::FWebSocketSessionAccessTokenDomain(
        const FWebSocketSessionAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        Wsclient(From.Wsclient),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken)
    {

    }

    FWebSocketSessionAccessTokenDomain::FSetUserIdTask::FSetUserIdTask(
        const TSharedPtr<FWebSocketSessionAccessTokenDomain>& Self,
        const Request::FSetUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FWebSocketSessionAccessTokenDomain::FSetUserIdTask::FSetUserIdTask(
        const FSetUserIdTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FWebSocketSessionAccessTokenDomain::FSetUserIdTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FWebSocketSessionAccessTokenDomain>> Result
    )
    {
        const auto ModelFuture = Self->Model();
        ModelFuture->StartSynchronousTask();
        ModelFuture->EnsureCompletion();
        if (ModelFuture->GetTask().IsError())
        {
            return ModelFuture->GetTask().Error();
        }
        const auto QueryNamespaceName = Self->NamespaceName;
        const auto SourceToken = Self->AccessToken;
        const TOptional<FString> SnapshotUserId = SourceToken.IsValid()
            ? SourceToken->GetUserId()
            : TOptional<FString>();
        const TOptional<int32> SnapshotTimeOffset = SourceToken.IsValid()
            ? SourceToken->GetTimeOffset()
            : TOptional<int32>();
        const auto TokenSnapshot = SourceToken.IsValid()
            ? MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken)
            : Gs2::Auth::Model::FAccessTokenPtr();
        Request
            ->WithContextStack(
                !Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()
                    ? Self->Gs2->DefaultContextStack
                    : Request->GetContextStack()
            )
            ->WithNamespaceName(QueryNamespaceName)
            ->WithAccessToken(TokenSnapshot.IsValid() ? TokenSnapshot->GetToken() : TOptional<FString>());
        const auto Future = Self->Wsclient->SetUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Gateway::Model::Cache::FWebSocketSessionCache::Put(
                    Self->Gs2->Cache,
                    ResultModel->GetItem()->GetNamespaceName(),
                    SnapshotUserId,
                    SnapshotTimeOffset,
                    ResultModel->GetItem()
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWebSocketSessionAccessTokenDomain::FSetUserIdTask>> FWebSocketSessionAccessTokenDomain::SetUserId(
        Request::FSetUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetUserIdTask>>(this->AsShared(), Request);
    }

    FString FWebSocketSessionAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FWebSocketSessionAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FWebSocketSessionAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FWebSocketSessionAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FWebSocketSessionAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FWebSocketSessionAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Model::FWebSocketSession>> Result
    )
    {
        TSharedPtr<Gs2::Gateway::Model::FWebSocketSession> Value;
        Gs2::Gateway::Model::Cache::FWebSocketSessionCache::TryGet(
            Self->Gs2->Cache,
            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->AccessToken->GetUserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
            &Value
        );
        *Result = Value;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWebSocketSessionAccessTokenDomain::FModelTask>> FWebSocketSessionAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FWebSocketSessionAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    FWebSocketSessionAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FWebSocketSessionAccessTokenDomain>& Self,
        TFunction<void(Gs2::Gateway::Model::FWebSocketSessionPtr)> Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FWebSocketSessionAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FWebSocketSessionAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Future = Self->Model();
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Item = Future->GetTask().Result();
        const auto ID = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWebSocketSessionAccessTokenDomain::FSubscribeWithInitialCallTask>> FWebSocketSessionAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Gateway::Model::FWebSocketSessionPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FWebSocketSessionAccessTokenDomain::Invalidate()
    {
        Gs2::Gateway::Model::Cache::FWebSocketSessionCache::Delete(
            Gs2->Cache,
            NamespaceName,
            AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FWebSocketSessionAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Gateway::Model::FWebSocketSessionPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Gateway::Domain::FGs2GatewayDomain> WeakService = Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? SourceToken->GetUserId()
            : TOptional<FString>();
        const TOptional<int32> RegisteredTimeOffset = SourceToken.IsValid()
            ? SourceToken->GetTimeOffset()
            : TOptional<int32>();
        const auto Parent = Gs2::Gateway::Model::Cache::FWebSocketSessionCache::CreateCacheParentKey(
            QueryNamespaceName,
            RegisteredUserId,
            RegisteredTimeOffset
        );
        return Gs2->Cache->Subscribe(
            Gs2::Gateway::Model::FWebSocketSession::TypeName,
            Parent,
            Gs2::Gateway::Model::Cache::FWebSocketSessionCache::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Gateway::Model::FWebSocketSession>(obj));
            },
            [WeakGs2, WeakService, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset() != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FWebSocketSessionAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot
                );
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FWebSocketSessionAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Gateway::Model::FWebSocketSession::TypeName,
            Gs2::Gateway::Model::Cache::FWebSocketSessionCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Gs2::Gateway::Model::Cache::FWebSocketSessionCache::CreateCacheKey(),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
