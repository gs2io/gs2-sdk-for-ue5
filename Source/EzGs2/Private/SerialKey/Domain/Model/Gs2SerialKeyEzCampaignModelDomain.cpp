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

#include "SerialKey/Domain/Model/Gs2SerialKeyEzCampaignModelDomain.h"

namespace Gs2::UE5::SerialKey::Domain::Model
{

    TOptional<FString> FEzCampaignModelDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzCampaignModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzCampaignModelDomain::CampaignModelName() const
    {
        return Domain->CampaignModelName;
    }

    FEzCampaignModelDomain::FEzCampaignModelDomain(
        Gs2::SerialKey::Domain::Model::FCampaignModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzCampaignModelDomain::FGetCampaignModelTask::FGetCampaignModelTask(
        TSharedPtr<FEzCampaignModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCampaignModelDomain::FGetCampaignModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::SerialKey::Model::FEzCampaignModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetCampaignModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::SerialKey::Request::FGetCampaignModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::SerialKey::Model::FEzCampaignModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzCampaignModelDomain::FGetCampaignModelTask>> FEzCampaignModelDomain::GetCampaignModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetCampaignModelTask>>(
            this->AsShared()
        );
    }

    FEzCampaignModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzCampaignModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCampaignModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::SerialKey::Model::FEzCampaignModelPtr> Result
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
                *Result = Gs2::UE5::SerialKey::Model::FEzCampaignModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzCampaignModelDomain::FModelTask>> FEzCampaignModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
