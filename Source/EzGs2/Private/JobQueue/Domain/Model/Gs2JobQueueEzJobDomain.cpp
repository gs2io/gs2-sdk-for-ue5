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

#include "JobQueue/Domain/Model/Gs2JobQueueEzJobDomain.h"

namespace Gs2::UE5::JobQueue::Domain::Model
{

    TOptional<bool> FEzJobDomain::AutoRun() const
    {
        return Domain->AutoRun;
    }

    TOptional<bool> FEzJobDomain::IsLastJob() const
    {
        return Domain->IsLastJob;
    }

    TOptional<bool> FEzJobDomain::NeedRetry() const
    {
        return Domain->NeedRetry;
    }

    TOptional<FString> FEzJobDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzJobDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzJobDomain::JobName() const
    {
        return Domain->JobName;
    }

    FEzJobDomain::FEzJobDomain(
        Gs2::JobQueue::Domain::Model::FJobDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::JobQueue::Domain::Model::FEzJobResultDomainPtr FEzJobDomain::JobResult(
        const int32 TryNumber
    ) const
    {
        return MakeShared<Gs2::UE5::JobQueue::Domain::Model::FEzJobResultDomain>(
            Domain->JobResult(
                TryNumber
            ),
            ProfileValue
        );
    }

    FEzJobDomain::FModelTask::FModelTask(
        TSharedPtr<FEzJobDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzJobDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::JobQueue::Model::FEzJobPtr> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FModelTask>(
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

    TSharedPtr<FAsyncTask<FEzJobDomain::FModelTask>> FEzJobDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzJobDomain::Subscribe(TFunction<void(Gs2::UE5::JobQueue::Model::FEzJobPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::JobQueue::Model::FJobPtr Item)
            {
                Callback(Gs2::UE5::JobQueue::Model::FEzJob::FromModel(Item));
            }
        );
    }

    void FEzJobDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
