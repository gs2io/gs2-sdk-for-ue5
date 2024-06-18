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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzSeasonGatheringDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzSeasonGatheringDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSeasonGatheringDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzSeasonGatheringDomain::SeasonName() const
    {
        return Domain->SeasonName;
    }

    TOptional<int64> FEzSeasonGatheringDomain::Season() const
    {
        return Domain->Season;
    }

    TOptional<int64> FEzSeasonGatheringDomain::Tier() const
    {
        return Domain->Tier;
    }

    TOptional<FString> FEzSeasonGatheringDomain::SeasonGatheringName() const
    {
        return Domain->SeasonGatheringName;
    }

    FEzSeasonGatheringDomain::FEzSeasonGatheringDomain(
        Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzSeasonGatheringDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSeasonGatheringDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSeasonGatheringDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzSeasonGatheringPtr> Result
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
                *Result = Gs2::UE5::Matchmaking::Model::FEzSeasonGathering::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSeasonGatheringDomain::FModelTask>> FEzSeasonGatheringDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSeasonGatheringDomain::Subscribe(TFunction<void(Gs2::UE5::Matchmaking::Model::FEzSeasonGatheringPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Matchmaking::Model::FSeasonGatheringPtr Item)
            {
                Callback(Gs2::UE5::Matchmaking::Model::FEzSeasonGathering::FromModel(Item));
            }
        );
    }

    void FEzSeasonGatheringDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
