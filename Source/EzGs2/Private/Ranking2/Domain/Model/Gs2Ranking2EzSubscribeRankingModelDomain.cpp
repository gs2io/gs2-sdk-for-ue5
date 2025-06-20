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
 *
 * deny overwrite
 */

#include "Ranking2/Domain/Model/Gs2Ranking2EzSubscribeRankingModelDomain.h"

#include "Ranking2/Domain/Model/Gs2Ranking2EzSubscribeRankingSeasonGameSessionDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzSubscribeRankingModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSubscribeRankingModelDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    FEzSubscribeRankingModelDomain::FEzSubscribeRankingModelDomain(
        Gs2::Ranking2::Domain::Model::FSubscribeRankingModelDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingSeasonGameSessionDomainPtr FEzSubscribeRankingModelDomain::SubscribeRankingSeason(
        const Util::FGameSessionPtr GameSession,
        const TOptional<int64> Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingSeasonGameSessionDomain>(
            Domain->SubscribeRankingSeason(
                GameSession->AccessToken(),
                Season
            ),
            GameSession,
            ConnectionValue
        );
    }

    FEzSubscribeRankingModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSubscribeRankingModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscribeRankingModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking2::Model::FEzSubscribeRankingModelPtr> Result
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
                *Result = Gs2::UE5::Ranking2::Model::FEzSubscribeRankingModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSubscribeRankingModelDomain::FModelTask>> FEzSubscribeRankingModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSubscribeRankingModelDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzSubscribeRankingModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking2::Model::FSubscribeRankingModelPtr Item)
            {
                Callback(Gs2::UE5::Ranking2::Model::FEzSubscribeRankingModel::FromModel(Item));
            }
        );
    }

    void FEzSubscribeRankingModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
