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

#include "Formation/Domain/Model/Gs2FormationEzMoldDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    TOptional<FString> FEzMoldDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzMoldDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzMoldDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzMoldDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzMoldDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzMoldDomain::MoldModelName() const
    {
        return Domain->MoldModelName;
    }

    FEzMoldDomain::FEzMoldDomain(
        Gs2::Formation::Domain::Model::FMoldDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Formation::Domain::Model::FEzFormDomainPtr FEzMoldDomain::Form(
        const int32 Index
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzFormDomain>(
            Domain->Form(
                Index
            ),
            ProfileValue
        );
    }

    FEzMoldDomain::FModelTask::FModelTask(
        TSharedPtr<FEzMoldDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMoldDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Formation::Model::FEzMoldPtr> Result
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
                *Result = Gs2::UE5::Formation::Model::FEzMold::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzMoldDomain::FModelTask>> FEzMoldDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzMoldDomain::Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzMoldPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Formation::Model::FMoldPtr Item)
            {
                Callback(Gs2::UE5::Formation::Model::FEzMold::FromModel(Item));
            }
        );
    }

    void FEzMoldDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
