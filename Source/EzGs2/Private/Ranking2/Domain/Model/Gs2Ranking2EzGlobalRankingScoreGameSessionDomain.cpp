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

#include "Ranking2/Domain/Model/Gs2Ranking2EzGlobalRankingScoreGameSessionDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzGlobalRankingScoreGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzGlobalRankingScoreGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzGlobalRankingScoreGameSessionDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<int64> FEzGlobalRankingScoreGameSessionDomain::Season() const
    {
        return Domain->Season;
    }

    FEzGlobalRankingScoreGameSessionDomain::FEzGlobalRankingScoreGameSessionDomain(
        Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzGlobalRankingScoreGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzGlobalRankingScoreGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGlobalRankingScoreGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking2::Model::FEzGlobalRankingScorePtr> Result
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
                *Result = Gs2::UE5::Ranking2::Model::FEzGlobalRankingScore::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzGlobalRankingScoreGameSessionDomain::FModelTask>> FEzGlobalRankingScoreGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzGlobalRankingScoreGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzGlobalRankingScorePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking2::Model::FGlobalRankingScorePtr Item)
            {
                Callback(Gs2::UE5::Ranking2::Model::FEzGlobalRankingScore::FromModel(Item));
            }
        );
    }

    void FEzGlobalRankingScoreGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
