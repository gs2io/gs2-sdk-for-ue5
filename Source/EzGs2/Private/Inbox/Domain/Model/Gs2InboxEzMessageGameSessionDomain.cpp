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

#include "Inbox/Domain/Model/Gs2InboxEzMessageGameSessionDomain.h"

namespace Gs2::UE5::Inbox::Domain::Model
{

    TOptional<FString> FEzMessageGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzMessageGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzMessageGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzMessageGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzMessageGameSessionDomain::MessageName() const
    {
        return Domain->MessageName;
    }

    FEzMessageGameSessionDomain::FEzMessageGameSessionDomain(
        Gs2::Inbox::Domain::Model::FMessageAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzMessageGameSessionDomain::FReadTask::FReadTask(
        TSharedPtr<FEzMessageGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMessageGameSessionDomain::FReadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Read(
                    MakeShared<Gs2::Inbox::Request::FReadMessageRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzMessageGameSessionDomain::FReadTask>> FEzMessageGameSessionDomain::Read(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FReadTask>>(
            this->AsShared()
        );
    }

    FEzMessageGameSessionDomain::FDeleteTask::FDeleteTask(
        TSharedPtr<FEzMessageGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMessageGameSessionDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Inbox::Request::FDeleteMessageRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzMessageGameSessionDomain::FDeleteTask>> FEzMessageGameSessionDomain::Delete(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(
            this->AsShared()
        );
    }

    FEzMessageGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzMessageGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMessageGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inbox::Model::FEzMessagePtr> Result
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
                *Result = Gs2::UE5::Inbox::Model::FEzMessage::FromModel(Task->GetTask().Result());
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

    Gs2::Core::Domain::CallbackID FEzMessageGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Inbox::Model::FEzMessagePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Inbox::Model::FMessagePtr Item)
            {
                Callback(Gs2::UE5::Inbox::Model::FEzMessage::FromModel(Item));
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
