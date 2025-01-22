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

#include "Gateway/Domain/Model/Gs2GatewayEzWebSocketSessionGameSessionDomain.h"

namespace Gs2::UE5::Gateway::Domain::Model
{

    TOptional<FString> FEzWebSocketSessionGameSessionDomain::Protocol() const
    {
        return Domain->Protocol;
    }

    TSharedPtr<TArray<FString>> FEzWebSocketSessionGameSessionDomain::SendConnectionIds() const
    {
        return Domain->SendConnectionIds;
    }

    TOptional<FString> FEzWebSocketSessionGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzWebSocketSessionGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzWebSocketSessionGameSessionDomain::FEzWebSocketSessionGameSessionDomain(
        Gs2::Gateway::Domain::Model::FWebSocketSessionAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzWebSocketSessionGameSessionDomain::FSetUserIdTask::FSetUserIdTask(
        TSharedPtr<FEzWebSocketSessionGameSessionDomain> Self,
        TOptional<bool> AllowConcurrentAccess
    ): Self(Self), AllowConcurrentAccess(AllowConcurrentAccess)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzWebSocketSessionGameSessionDomain::FSetUserIdTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Gateway::Domain::Model::FEzWebSocketSessionGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->SetUserId(
                    MakeShared<Gs2::Gateway::Request::FSetUserIdRequest>()
                        ->WithAllowConcurrentAccess(AllowConcurrentAccess)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Gateway::Domain::Model::FEzWebSocketSessionGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzWebSocketSessionGameSessionDomain::FSetUserIdTask>> FEzWebSocketSessionGameSessionDomain::SetUserId(
        TOptional<bool> AllowConcurrentAccess
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSetUserIdTask>>(
            this->AsShared(),
            AllowConcurrentAccess
        );
    }

    FEzWebSocketSessionGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzWebSocketSessionGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzWebSocketSessionGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Gateway::Model::FEzWebSocketSessionPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Gateway::Model::FEzWebSocketSession::FromModel(Task->GetTask().Result());
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzWebSocketSessionGameSessionDomain::FModelTask>> FEzWebSocketSessionGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzWebSocketSessionGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Gateway::Model::FEzWebSocketSessionPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Gateway::Model::FWebSocketSessionPtr Item)
            {
                Callback(Gs2::UE5::Gateway::Model::FEzWebSocketSession::FromModel(Item));
            }
        );
    }

    void FEzWebSocketSessionGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
