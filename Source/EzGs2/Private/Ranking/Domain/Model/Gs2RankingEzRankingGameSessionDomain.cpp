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

#include "Ranking/Domain/Model/Gs2RankingEzRankingGameSessionDomain.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    TOptional<FString> FEzRankingGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRankingGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzRankingGameSessionDomain::CategoryName() const
    {
        return Domain->CategoryName;
    }

    TOptional<FString> FEzRankingGameSessionDomain::AdditionalScopeName() const
    {
        return Domain->AdditionalScopeName;
    }

    TOptional<FString> FEzRankingGameSessionDomain::ScorerUserId() const
    {
        return Domain->ScorerUserId;
    }

    TOptional<int64> FEzRankingGameSessionDomain::Index() const
    {
        return Domain->Index;
    }

    FEzRankingGameSessionDomain::FEzRankingGameSessionDomain(
        Gs2::Ranking::Domain::Model::FRankingAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzRankingGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRankingGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRankingGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking::Model::FEzRankingPtr> Result
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
                *Result = Gs2::UE5::Ranking::Model::FEzRanking::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRankingGameSessionDomain::FModelTask>> FEzRankingGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzRankingGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking::Model::FEzRankingPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking::Model::FRankingPtr Item)
            {
                Callback(Gs2::UE5::Ranking::Model::FEzRanking::FromModel(Item));
            }
        );
    }

    void FEzRankingGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
