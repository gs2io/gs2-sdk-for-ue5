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

#include "JobQueue/Domain/Model/Gs2JobQueueEzJobResultDomain.h"

namespace Gs2::UE5::JobQueue::Domain::Model
{

    TOptional<FString> FEzJobResultDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzJobResultDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzJobResultDomain::JobName() const
    {
        return Domain->JobName;
    }

    TOptional<int32> FEzJobResultDomain::TryNumber() const
    {
        return Domain->TryNumber;
    }

    FEzJobResultDomain::FEzJobResultDomain(
        Gs2::JobQueue::Domain::Model::FJobResultDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzJobResultDomain::FModelTask::FModelTask(
        TSharedPtr<FEzJobResultDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzJobResultDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::JobQueue::Model::FEzJobResultPtr> Result
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
                *Result = Gs2::UE5::JobQueue::Model::FEzJobResult::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzJobResultDomain::FModelTask>> FEzJobResultDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzJobResultDomain::Subscribe(TFunction<void(Gs2::UE5::JobQueue::Model::FEzJobResultPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::JobQueue::Model::FJobResultPtr Item)
            {
                Callback(Gs2::UE5::JobQueue::Model::FEzJobResult::FromModel(Item));
            }
        );
    }

    void FEzJobResultDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
