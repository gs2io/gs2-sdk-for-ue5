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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzGatheringDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzGatheringDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzGatheringDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzGatheringDomain::GatheringName() const
    {
        return Domain->GatheringName;
    }

    FEzGatheringDomain::FEzGatheringDomain(
        Gs2::Matchmaking::Domain::Model::FGatheringDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzGatheringDomain::FModelTask::FModelTask(
        TSharedPtr<FEzGatheringDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGatheringDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzGatheringPtr> Result
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
                *Result = Gs2::UE5::Matchmaking::Model::FEzGathering::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzGatheringDomain::FModelTask>> FEzGatheringDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzGatheringDomain::Subscribe(TFunction<void(Gs2::UE5::Matchmaking::Model::FEzGatheringPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Matchmaking::Model::FGatheringPtr Item)
            {
                Callback(Gs2::UE5::Matchmaking::Model::FEzGathering::FromModel(Item));
            }
        );
    }

    void FEzGatheringDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
