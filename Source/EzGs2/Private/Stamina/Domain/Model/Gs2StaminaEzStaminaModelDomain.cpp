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

#include "Stamina/Domain/Model/Gs2StaminaEzStaminaModelDomain.h"

namespace Gs2::UE5::Stamina::Domain::Model
{

    TOptional<FString> FEzStaminaModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzStaminaModelDomain::StaminaName() const
    {
        return Domain->StaminaName;
    }

    FEzStaminaModelDomain::FEzStaminaModelDomain(
        Gs2::Stamina::Domain::Model::FStaminaModelDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzStaminaModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzStaminaModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStaminaModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Stamina::Model::FEzStaminaModelPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Stamina::Model::FEzStaminaModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzStaminaModelDomain::FModelTask>> FEzStaminaModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzStaminaModelDomain::Subscribe(TFunction<void(Gs2::UE5::Stamina::Model::FEzStaminaModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Stamina::Model::FStaminaModelPtr Item)
            {
                Callback(Gs2::UE5::Stamina::Model::FEzStaminaModel::FromModel(Item));
            }
        );
    }

    void FEzStaminaModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
