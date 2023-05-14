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

#include "Gateway/Domain/Model/WebSocketSession.h"
#include "Gateway/Domain/Model/Namespace.h"
#include "Gateway/Domain/Model/WebSocketSession.h"
#include "Gateway/Domain/Model/WebSocketSessionAccessToken.h"
#include "Gateway/Domain/Model/FirebaseToken.h"
#include "Gateway/Domain/Model/FirebaseTokenAccessToken.h"
#include "Gateway/Domain/Model/User.h"
#include "Gateway/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Gateway::Domain::Model
{

    FWebSocketSessionDomain::FWebSocketSessionDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr Wssession,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Gateway::FGs2GatewayRestClient>(Session)),
        Wssession(Wssession),
        Wsclient(MakeShared<Gs2::Gateway::FGs2GatewayWebSocketClient>(Wssession)),
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
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FWebSocketSessionDomain::FSetUserIdTask::FSetUserIdTask(
        const TSharedPtr<FWebSocketSessionDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "WebSocketSession"
                );
                const auto Key = Gs2::Gateway::Domain::Model::FWebSocketSessionDomain::CreateCacheKey(
                );
                Self->Cache->Put(
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
        return FString() +
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
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Gateway::Model::FWebSocketSession>(
            Self->ParentKey,
            Gs2::Gateway::Domain::Model::FWebSocketSessionDomain::CreateCacheKey(
            )
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FWebSocketSessionDomain::FModelTask>> FWebSocketSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FWebSocketSessionDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

