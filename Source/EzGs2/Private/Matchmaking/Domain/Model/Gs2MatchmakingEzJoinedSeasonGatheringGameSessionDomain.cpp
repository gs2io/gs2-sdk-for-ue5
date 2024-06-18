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

#include "Matchmaking/Domain/Model/Gs2MatchmakingEzJoinedSeasonGatheringGameSessionDomain.h"

namespace Gs2::UE5::Matchmaking::Domain::Model
{

    TOptional<FString> FEzJoinedSeasonGatheringGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzJoinedSeasonGatheringGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzJoinedSeasonGatheringGameSessionDomain::SeasonName() const
    {
        return Domain->SeasonName;
    }

    TOptional<int64> FEzJoinedSeasonGatheringGameSessionDomain::Season() const
    {
        return Domain->Season;
    }

    FEzJoinedSeasonGatheringGameSessionDomain::FEzJoinedSeasonGatheringGameSessionDomain(
        Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzJoinedSeasonGatheringGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzJoinedSeasonGatheringGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzJoinedSeasonGatheringGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGatheringPtr> Result
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
                *Result = Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGathering::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzJoinedSeasonGatheringGameSessionDomain::FModelTask>> FEzJoinedSeasonGatheringGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzJoinedSeasonGatheringGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGatheringPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr Item)
            {
                Callback(Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGathering::FromModel(Item));
            }
        );
    }

    void FEzJoinedSeasonGatheringGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
