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

#include "Formation/Domain/Model/Gs2FormationEzMoldModelDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    TOptional<FString> FEzMoldModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzMoldModelDomain::MoldModelName() const
    {
        return Domain->MoldModelName;
    }

    FEzMoldModelDomain::FEzMoldModelDomain(
        Gs2::Formation::Domain::Model::FMoldModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzMoldModelDomain::FGetMoldModelTask::FGetMoldModelTask(
        TSharedPtr<FEzMoldModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMoldModelDomain::FGetMoldModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzMoldModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetMoldModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Formation::Request::FGetMoldModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Formation::Model::FEzMoldModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzMoldModelDomain::FGetMoldModelTask>> FEzMoldModelDomain::GetMoldModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetMoldModelTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzFormModelDomainPtr FEzMoldModelDomain::FormModel(
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzFormModelDomain>(
            Domain->FormModel(
            ),
            ProfileValue
        );
    }

    FEzMoldModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzMoldModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMoldModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Formation::Model::FEzMoldModelPtr> Result
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
                *Result = Gs2::UE5::Formation::Model::FEzMoldModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzMoldModelDomain::FModelTask>> FEzMoldModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzMoldModelDomain::Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzMoldModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Formation::Model::FMoldModelPtr Item)
            {
                Callback(Gs2::UE5::Formation::Model::FEzMoldModel::FromModel(Item));
            }
        );
    }

    void FEzMoldModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
