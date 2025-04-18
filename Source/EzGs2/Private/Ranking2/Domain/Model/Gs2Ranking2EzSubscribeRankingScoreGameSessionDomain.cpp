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

#include "Ranking2/Domain/Model/Gs2Ranking2EzSubscribeRankingScoreGameSessionDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzSubscribeRankingScoreGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSubscribeRankingScoreGameSessionDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<int64> FEzSubscribeRankingScoreGameSessionDomain::Season() const
    {
        return Domain->Season;
    }

    TOptional<FString> FEzSubscribeRankingScoreGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzSubscribeRankingScoreGameSessionDomain::FEzSubscribeRankingScoreGameSessionDomain(
        Gs2::Ranking2::Domain::Model::FSubscribeRankingScoreAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzSubscribeRankingScoreGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSubscribeRankingScoreGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscribeRankingScoreGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking2::Model::FEzSubscribeRankingScorePtr> Result
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
                *Result = Gs2::UE5::Ranking2::Model::FEzSubscribeRankingScore::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSubscribeRankingScoreGameSessionDomain::FModelTask>> FEzSubscribeRankingScoreGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSubscribeRankingScoreGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzSubscribeRankingScorePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking2::Model::FSubscribeRankingScorePtr Item)
            {
                Callback(Gs2::UE5::Ranking2::Model::FEzSubscribeRankingScore::FromModel(Item));
            }
        );
    }

    void FEzSubscribeRankingScoreGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
