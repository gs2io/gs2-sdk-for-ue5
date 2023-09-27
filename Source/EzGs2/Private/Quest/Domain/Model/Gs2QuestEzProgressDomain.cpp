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

#include "Quest/Domain/Model/Gs2QuestEzProgressDomain.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    TOptional<FString> FEzProgressDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzProgressDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzProgressDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzProgressDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzProgressDomain::FEzProgressDomain(
        Gs2::Quest::Domain::Model::FProgressDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzProgressDomain::FModelTask::FModelTask(
        TSharedPtr<FEzProgressDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProgressDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Quest::Model::FEzProgressPtr> Result
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
                *Result = Gs2::UE5::Quest::Model::FEzProgress::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzProgressDomain::FModelTask>> FEzProgressDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzProgressDomain::Subscribe(TFunction<void(Gs2::UE5::Quest::Model::FEzProgressPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Quest::Model::FProgressPtr Item)
            {
                Callback(Gs2::UE5::Quest::Model::FEzProgress::FromModel(Item));
            }
        );
    }

    void FEzProgressDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
