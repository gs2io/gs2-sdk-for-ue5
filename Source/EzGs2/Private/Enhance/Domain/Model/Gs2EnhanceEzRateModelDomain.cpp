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

#include "Enhance/Domain/Model/Gs2EnhanceEzRateModelDomain.h"

namespace Gs2::UE5::Enhance::Domain::Model
{

    TOptional<FString> FEzRateModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRateModelDomain::RateName() const
    {
        return Domain->RateName;
    }

    FEzRateModelDomain::FEzRateModelDomain(
        Gs2::Enhance::Domain::Model::FRateModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzRateModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRateModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRateModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Enhance::Model::FEzRateModelPtr> Result
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
                *Result = Gs2::UE5::Enhance::Model::FEzRateModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRateModelDomain::FModelTask>> FEzRateModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzRateModelDomain::Subscribe(TFunction<void(Gs2::UE5::Enhance::Model::FEzRateModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Enhance::Model::FRateModelPtr Item)
            {
                Callback(Gs2::UE5::Enhance::Model::FEzRateModel::FromModel(Item));
            }
        );
    }

    void FEzRateModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
