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

#include "Schedule/Domain/Model/Gs2ScheduleEzEventDomain.h"

namespace Gs2::UE5::Schedule::Domain::Model
{

    TOptional<bool> FEzEventDomain::InSchedule() const
    {
        return Domain->InSchedule;
    }

    TOptional<int64> FEzEventDomain::ScheduleStartAt() const
    {
        return Domain->ScheduleStartAt;
    }

    TOptional<int64> FEzEventDomain::ScheduleEndAt() const
    {
        return Domain->ScheduleEndAt;
    }

    TOptional<FString> FEzEventDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzEventDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzEventDomain::EventName() const
    {
        return Domain->EventName;
    }

    FEzEventDomain::FEzEventDomain(
        Gs2::Schedule::Domain::Model::FEventDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzEventDomain::FModelTask::FModelTask(
        TSharedPtr<FEzEventDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzEventDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Schedule::Model::FEzEventPtr> Result
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
                *Result = Gs2::UE5::Schedule::Model::FEzEvent::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzEventDomain::FModelTask>> FEzEventDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzEventDomain::Subscribe(TFunction<void(Gs2::UE5::Schedule::Model::FEzEventPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Schedule::Model::FEventPtr Item)
            {
                Callback(Gs2::UE5::Schedule::Model::FEzEvent::FromModel(Item));
            }
        );
    }

    void FEzEventDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
