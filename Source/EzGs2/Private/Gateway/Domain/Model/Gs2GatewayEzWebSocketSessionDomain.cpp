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

#include "Gateway/Domain/Model/Gs2GatewayEzWebSocketSessionDomain.h"

namespace Gs2::UE5::Gateway::Domain::Model
{

    TOptional<FString> FEzWebSocketSessionDomain::Protocol() const
    {
        return Domain->Protocol;
    }

    TOptional<FString> FEzWebSocketSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzWebSocketSessionDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzWebSocketSessionDomain::FEzWebSocketSessionDomain(
        Gs2::Gateway::Domain::Model::FWebSocketSessionDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzWebSocketSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzWebSocketSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzWebSocketSessionDomain::FModelTask::Action(
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

    TSharedPtr<FAsyncTask<FEzWebSocketSessionDomain::FModelTask>> FEzWebSocketSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzWebSocketSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Gateway::Model::FEzWebSocketSessionPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Gateway::Model::FWebSocketSessionPtr Item)
            {
                Callback(Gs2::UE5::Gateway::Model::FEzWebSocketSession::FromModel(Item));
            }
        );
    }

    void FEzWebSocketSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
