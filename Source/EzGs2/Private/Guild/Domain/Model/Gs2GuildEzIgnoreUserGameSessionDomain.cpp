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

#include "Guild/Domain/Model/Gs2GuildEzIgnoreUserGameSessionDomain.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    TOptional<FString> FEzIgnoreUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzIgnoreUserGameSessionDomain::GuildModelName() const
    {
        return Domain->GuildModelName;
    }

    TOptional<FString> FEzIgnoreUserGameSessionDomain::GuildName() const
    {
        return Domain->GuildName();
    }

    FEzIgnoreUserGameSessionDomain::FEzIgnoreUserGameSessionDomain(
        Gs2::Guild::Domain::Model::FIgnoreUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzIgnoreUserGameSessionDomain::FDeleteIgnoreUserTask::FDeleteIgnoreUserTask(
        TSharedPtr<FEzIgnoreUserGameSessionDomain> Self,
        FString UserId
    ): Self(Self), UserId(UserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzIgnoreUserGameSessionDomain::FDeleteIgnoreUserTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzIgnoreUserGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Guild::Request::FDeleteIgnoreUserRequest>()
                        ->WithUserId(UserId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Guild::Domain::Model::FEzIgnoreUserGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzIgnoreUserGameSessionDomain::FDeleteIgnoreUserTask>> FEzIgnoreUserGameSessionDomain::DeleteIgnoreUser(
        FString UserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteIgnoreUserTask>>(
            this->AsShared(),
            UserId
        );
    }

    FEzIgnoreUserGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzIgnoreUserGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzIgnoreUserGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Guild::Model::FEzIgnoreUserPtr> Result
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
                *Result = Gs2::UE5::Guild::Model::FEzIgnoreUser::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzIgnoreUserGameSessionDomain::FModelTask>> FEzIgnoreUserGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzIgnoreUserGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Guild::Model::FEzIgnoreUserPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Guild::Model::FIgnoreUserPtr Item)
            {
                Callback(Gs2::UE5::Guild::Model::FEzIgnoreUser::FromModel(Item));
            }
        );
    }

    void FEzIgnoreUserGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
