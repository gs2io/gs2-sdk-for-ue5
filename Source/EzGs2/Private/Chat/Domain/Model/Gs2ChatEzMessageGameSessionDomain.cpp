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

#include "Chat/Domain/Model/Gs2ChatEzMessageGameSessionDomain.h"

namespace Gs2::UE5::Chat::Domain::Model
{

    TOptional<FString> FEzMessageGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzMessageGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzMessageGameSessionDomain::RoomName() const
    {
        return Domain->RoomName;
    }

    TOptional<FString> FEzMessageGameSessionDomain::Password() const
    {
        return Domain->Password;
    }

    TOptional<FString> FEzMessageGameSessionDomain::MessageName() const
    {
        return Domain->MessageName;
    }

    FEzMessageGameSessionDomain::FEzMessageGameSessionDomain(
        Gs2::Chat::Domain::Model::FMessageAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzMessageGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzMessageGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMessageGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Chat::Model::FEzMessagePtr> Result
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
                *Result = Gs2::UE5::Chat::Model::FEzMessage::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzMessageGameSessionDomain::FModelTask>> FEzMessageGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzMessageGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Chat::Model::FEzMessagePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Chat::Model::FMessagePtr Item)
            {
                Callback(Gs2::UE5::Chat::Model::FEzMessage::FromModel(Item));
            }
        );
    }

    void FEzMessageGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
