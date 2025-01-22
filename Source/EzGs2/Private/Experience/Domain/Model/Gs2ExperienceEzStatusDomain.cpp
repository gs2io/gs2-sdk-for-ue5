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

#include "Experience/Domain/Model/Gs2ExperienceEzStatusDomain.h"

namespace Gs2::UE5::Experience::Domain::Model
{

    TOptional<FString> FEzStatusDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzStatusDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzStatusDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzStatusDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzStatusDomain::ExperienceName() const
    {
        return Domain->ExperienceName;
    }

    TOptional<FString> FEzStatusDomain::PropertyId() const
    {
        return Domain->PropertyId;
    }

    FEzStatusDomain::FEzStatusDomain(
        Gs2::Experience::Domain::Model::FStatusDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzStatusDomain::FModelTask::FModelTask(
        TSharedPtr<FEzStatusDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStatusDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Experience::Model::FEzStatusPtr> Result
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
                *Result = Gs2::UE5::Experience::Model::FEzStatus::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzStatusDomain::FModelTask>> FEzStatusDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzStatusDomain::Subscribe(TFunction<void(Gs2::UE5::Experience::Model::FEzStatusPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Experience::Model::FStatusPtr Item)
            {
                Callback(Gs2::UE5::Experience::Model::FEzStatus::FromModel(Item));
            }
        );
    }

    void FEzStatusDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
