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

#include "Money2/Domain/Model/Gs2Money2EzSubscriptionStatusDomain.h"

namespace Gs2::UE5::Money2::Domain::Model
{

    TOptional<FString> FEzSubscriptionStatusDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSubscriptionStatusDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzSubscriptionStatusDomain::ContentName() const
    {
        return Domain->ContentName;
    }

    FEzSubscriptionStatusDomain::FEzSubscriptionStatusDomain(
        Gs2::Money2::Domain::Model::FSubscriptionStatusDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzSubscriptionStatusDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSubscriptionStatusDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscriptionStatusDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Money2::Model::FEzSubscriptionStatusPtr> Result
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
                *Result = Gs2::UE5::Money2::Model::FEzSubscriptionStatus::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSubscriptionStatusDomain::FModelTask>> FEzSubscriptionStatusDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSubscriptionStatusDomain::Subscribe(TFunction<void(Gs2::UE5::Money2::Model::FEzSubscriptionStatusPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Money2::Model::FSubscriptionStatusPtr Item)
            {
                Callback(Gs2::UE5::Money2::Model::FEzSubscriptionStatus::FromModel(Item));
            }
        );
    }

    void FEzSubscriptionStatusDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
