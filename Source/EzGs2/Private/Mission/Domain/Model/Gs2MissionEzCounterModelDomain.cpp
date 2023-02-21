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

#include "Mission/Domain/Model/Gs2MissionEzCounterModelDomain.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    TOptional<FString> FEzCounterModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzCounterModelDomain::CounterName() const
    {
        return Domain->CounterName;
    }

    FEzCounterModelDomain::FEzCounterModelDomain(
        Gs2::Mission::Domain::Model::FCounterModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzCounterModelDomain::FGetCounterModelTask::FGetCounterModelTask(
        TSharedPtr<FEzCounterModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCounterModelDomain::FGetCounterModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetCounterModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Mission::Request::FGetCounterModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Mission::Model::FEzCounterModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzCounterModelDomain::FGetCounterModelTask>> FEzCounterModelDomain::GetCounterModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetCounterModelTask>>(
            this->AsShared()
        );
    }

    FEzCounterModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzCounterModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCounterModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterModelPtr> Result
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
                *Result = Gs2::UE5::Mission::Model::FEzCounterModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzCounterModelDomain::FModelTask>> FEzCounterModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
