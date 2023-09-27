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

#include "AdReward/Domain/Model/Gs2AdRewardEzPointGameSessionDomain.h"

namespace Gs2::UE5::AdReward::Domain::Model
{

    TOptional<FString> FEzPointGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzPointGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzPointGameSessionDomain::FEzPointGameSessionDomain(
        Gs2::AdReward::Domain::Model::FPointAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzPointGameSessionDomain::FGetPointTask::FGetPointTask(
        TSharedPtr<FEzPointGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPointGameSessionDomain::FGetPointTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::AdReward::Model::FEzPoint>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetPointTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::AdReward::Request::FGetPointRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::AdReward::Model::FEzPoint::FromModel(
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

    TSharedPtr<FAsyncTask<FEzPointGameSessionDomain::FGetPointTask>> FEzPointGameSessionDomain::GetPoint(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetPointTask>>(
            this->AsShared()
        );
    }

    FEzPointGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzPointGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPointGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::AdReward::Model::FEzPointPtr> Result
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
                *Result = Gs2::UE5::AdReward::Model::FEzPoint::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzPointGameSessionDomain::FModelTask>> FEzPointGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzPointGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::AdReward::Model::FEzPointPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::AdReward::Model::FPointPtr Item)
            {
                Callback(Gs2::UE5::AdReward::Model::FEzPoint::FromModel(Item));
            }
        );
    }

    void FEzPointGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
