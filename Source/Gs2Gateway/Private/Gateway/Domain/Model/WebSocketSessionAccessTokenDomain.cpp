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

#include "Gateway/Domain/Model/WebSocketSessionAccessToken.h"
#include "Gateway/Domain/Model/WebSocketSession.h"
#include "Gateway/Domain/Model/Namespace.h"
#include "Gateway/Domain/Model/WebSocketSession.h"
#include "Gateway/Domain/Model/WebSocketSessionAccessToken.h"
#include "Gateway/Domain/Model/FirebaseToken.h"
#include "Gateway/Domain/Model/FirebaseTokenAccessToken.h"
#include "Gateway/Domain/Model/User.h"
#include "Gateway/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

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
        AccessToken(AccessToken),
        ParentKey(Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "WebSocketSession"
        ))
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
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
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
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
                const auto ParentKey = Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "WebSocketSession"
                );
                const auto Key = Gs2::Gateway::Domain::Model::FWebSocketSessionDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Gateway::Model::FWebSocketSession::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Gateway::Model::FWebSocketSession> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Gateway::Model::FWebSocketSession>(
            Self->ParentKey,
            Gs2::Gateway::Domain::Model::FWebSocketSessionDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWebSocketSessionAccessTokenDomain::FModelTask>> FWebSocketSessionAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FWebSocketSessionAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FWebSocketSessionAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Gateway::Model::FWebSocketSessionPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Gateway::Model::FWebSocketSession::TypeName,
            ParentKey,
            Gs2::Gateway::Domain::Model::FWebSocketSessionDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Gateway::Model::FWebSocketSession>(obj));
            }
        );
    }

    void FWebSocketSessionAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Gateway::Model::FWebSocketSession::TypeName,
            ParentKey,
            Gs2::Gateway::Domain::Model::FWebSocketSessionDomain::CreateCacheKey(
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

