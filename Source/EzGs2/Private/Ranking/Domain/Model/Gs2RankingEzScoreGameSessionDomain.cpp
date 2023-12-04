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

#include "Ranking/Domain/Model/Gs2RankingEzScoreGameSessionDomain.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    TOptional<FString> FEzScoreGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzScoreGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzScoreGameSessionDomain::CategoryName() const
    {
        return Domain->CategoryName;
    }

    TOptional<FString> FEzScoreGameSessionDomain::ScorerUserId() const
    {
        return Domain->ScorerUserId;
    }

    TOptional<FString> FEzScoreGameSessionDomain::UniqueId() const
    {
        return Domain->UniqueId;
    }

    FEzScoreGameSessionDomain::FEzScoreGameSessionDomain(
        Gs2::Ranking::Domain::Model::FScoreAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzScoreGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzScoreGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzScoreGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking::Model::FEzScorePtr> Result
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
                *Result = Gs2::UE5::Ranking::Model::FEzScore::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzScoreGameSessionDomain::FModelTask>> FEzScoreGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzScoreGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking::Model::FEzScorePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking::Model::FScorePtr Item)
            {
                Callback(Gs2::UE5::Ranking::Model::FEzScore::FromModel(Item));
            }
        );
    }

    void FEzScoreGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
