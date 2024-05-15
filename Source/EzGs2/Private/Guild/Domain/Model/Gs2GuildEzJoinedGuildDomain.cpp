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

#include "Guild/Domain/Model/Gs2GuildEzJoinedGuildDomain.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    TOptional<FString> FEzJoinedGuildDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzJoinedGuildDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzJoinedGuildDomain::GuildModelName() const
    {
        return Domain->GuildModelName;
    }

    TOptional<FString> FEzJoinedGuildDomain::GuildName() const
    {
        return Domain->GuildName;
    }

    FEzJoinedGuildDomain::FEzJoinedGuildDomain(
        Gs2::Guild::Domain::Model::FJoinedGuildDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzJoinedGuildDomain::FModelTask::FModelTask(
        TSharedPtr<FEzJoinedGuildDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzJoinedGuildDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Guild::Model::FEzJoinedGuildPtr> Result
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
                *Result = Gs2::UE5::Guild::Model::FEzJoinedGuild::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzJoinedGuildDomain::FModelTask>> FEzJoinedGuildDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzJoinedGuildDomain::Subscribe(TFunction<void(Gs2::UE5::Guild::Model::FEzJoinedGuildPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Guild::Model::FJoinedGuildPtr Item)
            {
                Callback(Gs2::UE5::Guild::Model::FEzJoinedGuild::FromModel(Item));
            }
        );
    }

    void FEzJoinedGuildDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
