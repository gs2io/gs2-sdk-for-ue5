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

#include "Lottery/Domain/Model/Gs2LotteryEzProbabilityDomain.h"

namespace Gs2::UE5::Lottery::Domain::Model
{

    TOptional<FString> FEzProbabilityDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzProbabilityDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzProbabilityDomain::LotteryName() const
    {
        return Domain->LotteryName;
    }

    TOptional<FString> FEzProbabilityDomain::PrizeId() const
    {
        return Domain->PrizeId;
    }

    FEzProbabilityDomain::FEzProbabilityDomain(
        Gs2::Lottery::Domain::Model::FProbabilityDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzProbabilityDomain::FModelTask::FModelTask(
        TSharedPtr<FEzProbabilityDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProbabilityDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Lottery::Model::FEzProbabilityPtr> Result
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
                *Result = Gs2::UE5::Lottery::Model::FEzProbability::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzProbabilityDomain::FModelTask>> FEzProbabilityDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzProbabilityDomain::Subscribe(TFunction<void(Gs2::UE5::Lottery::Model::FEzProbabilityPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Lottery::Model::FProbabilityPtr Item)
            {
                Callback(Gs2::UE5::Lottery::Model::FEzProbability::FromModel(Item));
            }
        );
    }

    void FEzProbabilityDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
