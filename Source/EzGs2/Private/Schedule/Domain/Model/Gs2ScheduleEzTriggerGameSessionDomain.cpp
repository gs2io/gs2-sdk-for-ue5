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

#include "Schedule/Domain/Model/Gs2ScheduleEzTriggerGameSessionDomain.h"

namespace Gs2::UE5::Schedule::Domain::Model
{

    TOptional<FString> FEzTriggerGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzTriggerGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzTriggerGameSessionDomain::TriggerName() const
    {
        return Domain->TriggerName;
    }

    FEzTriggerGameSessionDomain::FEzTriggerGameSessionDomain(
        Gs2::Schedule::Domain::Model::FTriggerAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzTriggerGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzTriggerGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzTriggerGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Schedule::Model::FEzTriggerPtr> Result
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
                *Result = Gs2::UE5::Schedule::Model::FEzTrigger::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzTriggerGameSessionDomain::FModelTask>> FEzTriggerGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzTriggerGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Schedule::Model::FEzTriggerPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Schedule::Model::FTriggerPtr Item)
            {
                Callback(Gs2::UE5::Schedule::Model::FEzTrigger::FromModel(Item));
            }
        );
    }

    void FEzTriggerGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
