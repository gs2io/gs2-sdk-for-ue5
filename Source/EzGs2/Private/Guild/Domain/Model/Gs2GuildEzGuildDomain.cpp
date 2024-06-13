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

#include "Guild/Domain/Model/Gs2GuildEzGuildDomain.h"

namespace Gs2::UE5::Guild::Domain::Model
{
    TOptional<FString> FEzGuildDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzGuildDomain::GuildModelName() const
    {
        return Domain->GuildModelName;
    }

    TOptional<FString> FEzGuildDomain::GuildName() const
    {
        return Domain->GuildName;
    }

    FEzGuildDomain::FEzGuildDomain(
        Gs2::Guild::Domain::Model::FGuildDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Guild::Domain::Model::FEzReceiveMemberRequestDomainPtr FEzGuildDomain::ReceiveMemberRequest(
        const FString FromUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Model::FEzReceiveMemberRequestDomain>(
            Domain->ReceiveMemberRequest(
                FromUserId
            ),
            ConnectionValue
        );
    }

    FEzGuildDomain::FModelTask::FModelTask(
        TSharedPtr<FEzGuildDomain> Self,
        Gs2::UE5::Util::IGameSessionPtr GameSession
    ): Self(Self), GameSession(GameSession)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGuildDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Guild::Model::FEzGuildPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model(this->GameSession->AccessToken());
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Guild::Model::FEzGuild::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzGuildDomain::FModelTask>> FEzGuildDomain::Model(
        Gs2::UE5::Util::FGameSessionPtr GameSession
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(
            MakeShared<Gs2::UE5::Guild::Domain::Model::FEzGuildDomain>(
                Domain,
                ConnectionValue
            ),
            GameSession
        );
    }

    Gs2::Core::Domain::CallbackID FEzGuildDomain::Subscribe(TFunction<void(Gs2::UE5::Guild::Model::FEzGuildPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Guild::Model::FGuildPtr Item)
            {
                Callback(Gs2::UE5::Guild::Model::FEzGuild::FromModel(Item));
            }
        );
    }

    void FEzGuildDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
