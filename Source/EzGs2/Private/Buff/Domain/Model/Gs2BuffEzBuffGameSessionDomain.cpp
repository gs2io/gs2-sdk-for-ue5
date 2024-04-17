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

#include "Buff/Domain/Model/Gs2BuffEzBuffGameSessionDomain.h"

#include "Core/Gs2Domain.h"

namespace Gs2::UE5::Buff::Domain::Model
{

    TOptional<FString> FEzBuffGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBuffGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzBuffGameSessionDomain::FEzBuffGameSessionDomain(
        Gs2::Buff::Domain::Model::FBuffAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzBuffGameSessionDomain::FApplyBuffTask::FApplyBuffTask(
        TSharedPtr<FEzBuffGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBuffGameSessionDomain::FApplyBuffTask::Action(
        TSharedPtr<TSharedPtr<Core::Domain::FGs2Domain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Apply(
                    MakeShared<Gs2::Buff::Request::FApplyBuffRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                auto Gs2 = MakeShared<Gs2::Core::Domain::FGs2>(
                    Self->Domain->Gs2->RestSession,
                    Self->Domain->Gs2->WebSocketSession,
                    Self->Domain->Gs2->DistributorNamespaceName
                );
                Gs2->DefaultContextStack = Self->Domain->NewContextStack;
                *Result = MakeShared<Core::Domain::FGs2Domain>(Gs2);
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

    TSharedPtr<FAsyncTask<FEzBuffGameSessionDomain::FApplyBuffTask>> FEzBuffGameSessionDomain::ApplyBuff(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FApplyBuffTask>>(
            this->AsShared()
        );
    }
}
