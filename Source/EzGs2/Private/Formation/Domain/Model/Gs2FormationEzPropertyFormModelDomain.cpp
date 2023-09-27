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

#include "Formation/Domain/Model/Gs2FormationEzPropertyFormModelDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    TOptional<FString> FEzPropertyFormModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzPropertyFormModelDomain::PropertyFormModelName() const
    {
        return Domain->PropertyFormModelName;
    }

    FEzPropertyFormModelDomain::FEzPropertyFormModelDomain(
        Gs2::Formation::Domain::Model::FPropertyFormModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzPropertyFormModelDomain::FGetPropertyFormModelTask::FGetPropertyFormModelTask(
        TSharedPtr<FEzPropertyFormModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPropertyFormModelDomain::FGetPropertyFormModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzPropertyFormModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetPropertyFormModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Formation::Request::FGetPropertyFormModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Formation::Model::FEzPropertyFormModel::FromModel(
                    Task->GetTask().Result()
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

    TSharedPtr<FAsyncTask<FEzPropertyFormModelDomain::FGetPropertyFormModelTask>> FEzPropertyFormModelDomain::GetPropertyFormModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetPropertyFormModelTask>>(
            this->AsShared()
        );
    }

    FEzPropertyFormModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzPropertyFormModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPropertyFormModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Formation::Model::FEzPropertyFormModelPtr> Result
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
                *Result = Gs2::UE5::Formation::Model::FEzPropertyFormModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzPropertyFormModelDomain::FModelTask>> FEzPropertyFormModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzPropertyFormModelDomain::Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzPropertyFormModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Formation::Model::FPropertyFormModelPtr Item)
            {
                Callback(Gs2::UE5::Formation::Model::FEzPropertyFormModel::FromModel(Item));
            }
        );
    }

    void FEzPropertyFormModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
