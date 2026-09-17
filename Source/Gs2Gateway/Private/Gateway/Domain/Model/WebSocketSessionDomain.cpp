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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Gateway::Domain::Model
{

    FWebSocketSessionDomain::FWebSocketSessionDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Gateway::Domain::FGs2GatewayDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Gateway::FGs2GatewayRestClient>(Gs2->RestSession)),
        Wsclient(MakeShared<Gs2::Gateway::FGs2GatewayWebSocketClient>(Gs2->WebSocketSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "WebSocketSession"
        ))
    {
    }

    FWebSocketSessionDomain::FWebSocketSessionDomain(
        const FWebSocketSessionDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        Wsclient(From.Wsclient),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FWebSocketSessionDomain::FSetUserIdTask::FSetUserIdTask(
        const TSharedPtr<FWebSocketSessionDomain>& Self,
        const Request::FSetUserIdByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FWebSocketSessionDomain::FSetUserIdTask::FSetUserIdTask(
        const FSetUserIdTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FWebSocketSessionDomain::FSetUserIdTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SetUserIdByUserId(
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

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Gateway::Model::Cache::FWebSocketSessionCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWebSocketSessionDomain::FSetUserIdTask>> FWebSocketSessionDomain::SetUserId(
        Request::FSetUserIdByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetUserIdTask>>(this->AsShared(), Request);
    }

    FString FWebSocketSessionDomain::CreateCacheParentKey(
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

    FString FWebSocketSessionDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FWebSocketSessionDomain::FModelTask::FModelTask(
        const TSharedPtr<FWebSocketSessionDomain> Self
    ): Self(Self)
    {

    }

    FWebSocketSessionDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FWebSocketSessionDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Model::FWebSocketSession>> Result
    )
    {
        const auto CacheParentKey = Gs2::Gateway::Model::Cache::FWebSocketSessionCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Gateway::Model::Cache::FWebSocketSessionCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Gateway::Model::FWebSocketSession::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Gateway::Model::FWebSocketSessionPtr Value;
                const auto CacheHit = Gs2::Gateway::Model::Cache::FWebSocketSessionCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FWebSocketSessionDomain::FModelTask>> FWebSocketSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FWebSocketSessionDomain::FModelTask>>(this->AsShared());
    }

    void FWebSocketSessionDomain::Invalidate()
    {
        Gs2::Gateway::Model::Cache::FWebSocketSessionCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
    }

    FWebSocketSessionDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FWebSocketSessionDomain>& Self,
        TFunction<void(Gs2::Gateway::Model::FWebSocketSessionPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FWebSocketSessionDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FWebSocketSessionDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FWebSocketSessionDomain::FSubscribeWithInitialCallTask>> FWebSocketSessionDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Gateway::Model::FWebSocketSessionPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FWebSocketSessionDomain::Subscribe(
        TFunction<void(Gs2::Gateway::Model::FWebSocketSessionPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Gateway::Model::Cache::FWebSocketSessionCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Gateway::Model::Cache::FWebSocketSessionCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Gateway::Domain::FGs2GatewayDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        return Gs2->Cache->Subscribe(
            Gs2::Gateway::Model::FWebSocketSession::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Gateway::Model::FWebSocketSession>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FWebSocketSessionDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FWebSocketSessionDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Gateway::Model::Cache::FWebSocketSessionCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Gateway::Model::Cache::FWebSocketSessionCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Gateway::Model::FWebSocketSession::TypeName,
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
