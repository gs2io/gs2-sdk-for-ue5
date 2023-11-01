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

#include "Mission/Domain/Model/Gs2MissionEzMissionGroupModelDomain.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    TOptional<FString> FEzMissionGroupModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzMissionGroupModelDomain::MissionGroupName() const
    {
        return Domain->MissionGroupName;
    }

    FEzMissionGroupModelDomain::FEzMissionGroupModelDomain(
        Gs2::Mission::Domain::Model::FMissionGroupModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Mission::Domain::Iterator::FEzDescribeMissionTaskModelsIteratorPtr FEzMissionGroupModelDomain::MissionTaskModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Mission::Domain::Iterator::FEzDescribeMissionTaskModelsIterator>(
            Domain->MissionTaskModels(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzMissionGroupModelDomain::SubscribeMissionTaskModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeMissionTaskModels(
            Callback
        );
    }

    void FEzMissionGroupModelDomain::UnsubscribeMissionTaskModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeMissionTaskModels(
            CallbackId
        );
    }

    Gs2::UE5::Mission::Domain::Model::FEzMissionTaskModelDomainPtr FEzMissionGroupModelDomain::MissionTaskModel(
        const FString MissionTaskName
    ) const
    {
        return MakeShared<Gs2::UE5::Mission::Domain::Model::FEzMissionTaskModelDomain>(
            Domain->MissionTaskModel(
                MissionTaskName
            ),
            ProfileValue
        );
    }

    FEzMissionGroupModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzMissionGroupModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMissionGroupModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionGroupModelPtr> Result
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
                *Result = Gs2::UE5::Mission::Model::FEzMissionGroupModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzMissionGroupModelDomain::FModelTask>> FEzMissionGroupModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzMissionGroupModelDomain::Subscribe(TFunction<void(Gs2::UE5::Mission::Model::FEzMissionGroupModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Mission::Model::FMissionGroupModelPtr Item)
            {
                Callback(Gs2::UE5::Mission::Model::FEzMissionGroupModel::FromModel(Item));
            }
        );
    }

    void FEzMissionGroupModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
