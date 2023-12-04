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

#include "Enchant/Domain/Model/Gs2EnchantEzRarityParameterStatusDomain.h"

namespace Gs2::UE5::Enchant::Domain::Model
{

    TOptional<FString> FEzRarityParameterStatusDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRarityParameterStatusDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzRarityParameterStatusDomain::ParameterName() const
    {
        return Domain->ParameterName;
    }

    TOptional<FString> FEzRarityParameterStatusDomain::PropertyId() const
    {
        return Domain->PropertyId;
    }

    FEzRarityParameterStatusDomain::FEzRarityParameterStatusDomain(
        Gs2::Enchant::Domain::Model::FRarityParameterStatusDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzRarityParameterStatusDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRarityParameterStatusDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRarityParameterStatusDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterStatusPtr> Result
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
                *Result = Gs2::UE5::Enchant::Model::FEzRarityParameterStatus::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRarityParameterStatusDomain::FModelTask>> FEzRarityParameterStatusDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzRarityParameterStatusDomain::Subscribe(TFunction<void(Gs2::UE5::Enchant::Model::FEzRarityParameterStatusPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Enchant::Model::FRarityParameterStatusPtr Item)
            {
                Callback(Gs2::UE5::Enchant::Model::FEzRarityParameterStatus::FromModel(Item));
            }
        );
    }

    void FEzRarityParameterStatusDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
