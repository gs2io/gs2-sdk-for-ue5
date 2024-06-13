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

#include "Guild/Domain/Model/Gs2GuildEzReceiveMemberRequestGameSessionDomain.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    TOptional<FString> FEzReceiveMemberRequestGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzReceiveMemberRequestGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzReceiveMemberRequestGameSessionDomain::GuildName() const
    {
        return Domain->GuildName();
    }

    TOptional<FString> FEzReceiveMemberRequestGameSessionDomain::FromUserId() const
    {
        return Domain->FromUserId;
    }

    FEzReceiveMemberRequestGameSessionDomain::FEzReceiveMemberRequestGameSessionDomain(
        Gs2::Guild::Domain::Model::FReceiveMemberRequestAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzReceiveMemberRequestGameSessionDomain::FAcceptTask::FAcceptTask(
        TSharedPtr<FEzReceiveMemberRequestGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzReceiveMemberRequestGameSessionDomain::FAcceptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzReceiveMemberRequestGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Accept();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Guild::Domain::Model::FEzReceiveMemberRequestGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzReceiveMemberRequestGameSessionDomain::FAcceptTask>> FEzReceiveMemberRequestGameSessionDomain::Accept() {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptTask>>(this->AsShared());
    }
    
    FEzReceiveMemberRequestGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzReceiveMemberRequestGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzReceiveMemberRequestGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Guild::Model::FEzReceiveMemberRequestPtr> Result
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
                *Result = Gs2::UE5::Guild::Model::FEzReceiveMemberRequest::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzReceiveMemberRequestGameSessionDomain::FModelTask>> FEzReceiveMemberRequestGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzReceiveMemberRequestGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Guild::Model::FEzReceiveMemberRequestPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Guild::Model::FReceiveMemberRequestPtr Item)
            {
                Callback(Gs2::UE5::Guild::Model::FEzReceiveMemberRequest::FromModel(Item));
            }
        );
    }

    void FEzReceiveMemberRequestGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
