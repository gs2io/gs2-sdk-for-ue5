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

#include "Enchant/Domain/Model/Gs2EnchantEzRarityParameterModelDomain.h"

namespace Gs2::UE5::Enchant::Domain::Model
{

    TOptional<FString> FEzRarityParameterModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRarityParameterModelDomain::ParameterName() const
    {
        return Domain->ParameterName;
    }

    FEzRarityParameterModelDomain::FEzRarityParameterModelDomain(
        Gs2::Enchant::Domain::Model::FRarityParameterModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzRarityParameterModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRarityParameterModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRarityParameterModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterModelPtr> Result
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
                *Result = Gs2::UE5::Enchant::Model::FEzRarityParameterModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRarityParameterModelDomain::FModelTask>> FEzRarityParameterModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzRarityParameterModelDomain::Subscribe(TFunction<void(Gs2::UE5::Enchant::Model::FEzRarityParameterModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Enchant::Model::FRarityParameterModelPtr Item)
            {
                Callback(Gs2::UE5::Enchant::Model::FEzRarityParameterModel::FromModel(Item));
            }
        );
    }

    void FEzRarityParameterModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
