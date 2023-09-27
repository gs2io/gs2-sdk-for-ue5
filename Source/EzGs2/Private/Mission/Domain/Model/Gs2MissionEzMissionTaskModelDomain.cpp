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

#include "Mission/Domain/Model/Gs2MissionEzMissionTaskModelDomain.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    TOptional<FString> FEzMissionTaskModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzMissionTaskModelDomain::MissionGroupName() const
    {
        return Domain->MissionGroupName;
    }

    TOptional<FString> FEzMissionTaskModelDomain::MissionTaskName() const
    {
        return Domain->MissionTaskName;
    }

    FEzMissionTaskModelDomain::FEzMissionTaskModelDomain(
        Gs2::Mission::Domain::Model::FMissionTaskModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzMissionTaskModelDomain::FGetMissionTaskModelTask::FGetMissionTaskModelTask(
        TSharedPtr<FEzMissionTaskModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMissionTaskModelDomain::FGetMissionTaskModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionTaskModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetMissionTaskModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Mission::Request::FGetMissionTaskModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Mission::Model::FEzMissionTaskModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzMissionTaskModelDomain::FGetMissionTaskModelTask>> FEzMissionTaskModelDomain::GetMissionTaskModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetMissionTaskModelTask>>(
            this->AsShared()
        );
    }

    FEzMissionTaskModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzMissionTaskModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMissionTaskModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionTaskModelPtr> Result
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
                *Result = Gs2::UE5::Mission::Model::FEzMissionTaskModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzMissionTaskModelDomain::FModelTask>> FEzMissionTaskModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzMissionTaskModelDomain::Subscribe(TFunction<void(Gs2::UE5::Mission::Model::FEzMissionTaskModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Mission::Model::FMissionTaskModelPtr Item)
            {
                Callback(Gs2::UE5::Mission::Model::FEzMissionTaskModel::FromModel(Item));
            }
        );
    }

    void FEzMissionTaskModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
