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

#include "LoginReward/Domain/Model/Gs2LoginRewardEzBonusModelDomain.h"

namespace Gs2::UE5::LoginReward::Domain::Model
{

    TOptional<FString> FEzBonusModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBonusModelDomain::BonusModelName() const
    {
        return Domain->BonusModelName;
    }

    FEzBonusModelDomain::FEzBonusModelDomain(
        Gs2::LoginReward::Domain::Model::FBonusModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzBonusModelDomain::FGetBonusModelTask::FGetBonusModelTask(
        TSharedPtr<FEzBonusModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBonusModelDomain::FGetBonusModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzBonusModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetBonusModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::LoginReward::Request::FGetBonusModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::LoginReward::Model::FEzBonusModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzBonusModelDomain::FGetBonusModelTask>> FEzBonusModelDomain::GetBonusModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetBonusModelTask>>(
            this->AsShared()
        );
    }

    FEzBonusModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzBonusModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBonusModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::LoginReward::Model::FEzBonusModelPtr> Result
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
                *Result = Gs2::UE5::LoginReward::Model::FEzBonusModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzBonusModelDomain::FModelTask>> FEzBonusModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzBonusModelDomain::Subscribe(TFunction<void(Gs2::UE5::LoginReward::Model::FEzBonusModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::LoginReward::Model::FBonusModelPtr Item)
            {
                Callback(Gs2::UE5::LoginReward::Model::FEzBonusModel::FromModel(Item));
            }
        );
    }

    void FEzBonusModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
