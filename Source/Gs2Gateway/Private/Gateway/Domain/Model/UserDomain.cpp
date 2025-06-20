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

#include "Gateway/Domain/Model/User.h"
#include "Gateway/Domain/Model/Namespace.h"
#include "Gateway/Domain/Model/WebSocketSession.h"
#include "Gateway/Domain/Model/WebSocketSessionAccessToken.h"
#include "Gateway/Domain/Model/FirebaseToken.h"
#include "Gateway/Domain/Model/FirebaseTokenAccessToken.h"
#include "Gateway/Domain/Model/User.h"
#include "Gateway/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Gateway::Domain::Model
{

    FUserDomain::FUserDomain(
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
        ParentKey(Gs2::Gateway::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
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

    FUserDomain::FSendNotificationTask::FSendNotificationTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FSendNotificationRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FSendNotificationTask::FSendNotificationTask(
        const FSendNotificationTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSendNotificationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FUserDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SendNotification(
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
            if (ResultModel->GetProtocol().IsSet())
            {
                Self->Protocol = Domain->Protocol = ResultModel->GetProtocol();
            }
            Self->SendConnectionIds = Domain->SendConnectionIds = ResultModel->GetSendConnectionIds();
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FSendNotificationTask>> FUserDomain::SendNotification(
        Request::FSendNotificationRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendNotificationTask>>(this->AsShared(), Request);
    }

    FUserDomain::FDisconnectTask::FDisconnectTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FDisconnectByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FDisconnectTask::FDisconnectTask(
        const FDisconnectTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FDisconnectTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DisconnectByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain>(
                    Self->Gs2,
                    Self->Service,
                    (*ResultModel->GetItems())[i]->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId()
                )
            );
            const auto ParentKey = Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                "WebSocketSession"
            );
            const auto Key = Gs2::Gateway::Domain::Model::FWebSocketSessionDomain::CreateCacheKey(
            );
            Self->Gs2->Cache->Put(
                Gs2::Gateway::Model::FWebSocketSession::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FDisconnectTask>> FUserDomain::Disconnect(
        Request::FDisconnectByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDisconnectTask>>(this->AsShared(), Request);
    }

    FUserDomain::FDisconnectAllTask::FDisconnectAllTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FDisconnectAllRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FDisconnectAllTask::FDisconnectAllTask(
        const FDisconnectAllTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FDisconnectAllTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FUserDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DisconnectAll(
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
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FDisconnectAllTask>> FUserDomain::DisconnectAll(
        Request::FDisconnectAllRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDisconnectAllTask>>(this->AsShared(), Request);
    }

    Gs2::Gateway::Domain::Iterator::FDescribeWebSocketSessionsByUserIdIteratorPtr FUserDomain::WebSocketSessions(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Gateway::Domain::Iterator::FDescribeWebSocketSessionsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeWebSocketSessions(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Gateway::Model::FWebSocketSession::TypeName,
            Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "WebSocketSession"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeWebSocketSessions(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Gateway::Model::FWebSocketSession::TypeName,
            Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "WebSocketSession"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain> FUserDomain::WebSocketSession(
    )
    {
        return MakeShared<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain> FUserDomain::FirebaseToken(
    )
    {
        return MakeShared<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

