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

#include "JobQueue/Domain/Model/Gs2JobQueueEzUserGameSessionDomain.h"

namespace Gs2::UE5::JobQueue::Domain::Model
{

    TOptional<bool> FEzUserGameSessionDomain::AutoRun() const
    {
        return Domain->AutoRun;
    }

    TOptional<bool> FEzUserGameSessionDomain::IsLastJob() const
    {
        return Domain->IsLastJob;
    }

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::JobQueue::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzUserGameSessionDomain::FRunTask::FRunTask(
        TSharedPtr<FEzUserGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FRunTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::JobQueue::Domain::Model::FEzJobGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Run(
                    MakeShared<Gs2::JobQueue::Request::FRunRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::JobQueue::Domain::Model::FEzJobGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FRunTask>> FEzUserGameSessionDomain::Run(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FRunTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::JobQueue::Domain::Model::FEzJobGameSessionDomainPtr FEzUserGameSessionDomain::Job(
        const FString JobName
    ) const
    {
        return MakeShared<Gs2::UE5::JobQueue::Domain::Model::FEzJobGameSessionDomain>(
            Domain->Job(
                JobName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
