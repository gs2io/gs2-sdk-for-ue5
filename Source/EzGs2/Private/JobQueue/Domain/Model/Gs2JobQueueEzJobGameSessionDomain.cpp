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

#include "JobQueue/Domain/Model/Gs2JobQueueEzJobGameSessionDomain.h"

namespace Gs2::UE5::JobQueue::Domain::Model
{

    TOptional<bool> FEzJobGameSessionDomain::AutoRun() const
    {
        return Domain->AutoRun;
    }

    TOptional<bool> FEzJobGameSessionDomain::IsLastJob() const
    {
        return Domain->IsLastJob;
    }

    TOptional<bool> FEzJobGameSessionDomain::NeedRetry() const
    {
        return Domain->NeedRetry;
    }

    TOptional<FString> FEzJobGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzJobGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzJobGameSessionDomain::JobName() const
    {
        return Domain->JobName;
    }

    FEzJobGameSessionDomain::FEzJobGameSessionDomain(
        Gs2::JobQueue::Domain::Model::FJobAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::JobQueue::Domain::Model::FEzJobResultGameSessionDomainPtr FEzJobGameSessionDomain::JobResult(
        const int32 TryNumber
    ) const
    {
        return MakeShared<Gs2::UE5::JobQueue::Domain::Model::FEzJobResultGameSessionDomain>(
            Domain->JobResult(
                TryNumber
            ),
            GameSession,
            ConnectionValue
        );
    }

    FEzJobGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzJobGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzJobGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::JobQueue::Model::FEzJobPtr> Result
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
                *Result = Gs2::UE5::JobQueue::Model::FEzJob::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzJobGameSessionDomain::FModelTask>> FEzJobGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzJobGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::JobQueue::Model::FEzJobPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::JobQueue::Model::FJobPtr Item)
            {
                Callback(Gs2::UE5::JobQueue::Model::FEzJob::FromModel(Item));
            }
        );
    }

    void FEzJobGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
