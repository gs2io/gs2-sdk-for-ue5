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

#include "Ranking2/Domain/Model/Gs2Ranking2EzGlobalRankingModelDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzGlobalRankingModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzGlobalRankingModelDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    FEzGlobalRankingModelDomain::FEzGlobalRankingModelDomain(
        Gs2::Ranking2::Domain::Model::FGlobalRankingModelDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingSeasonDomainPtr FEzGlobalRankingModelDomain::GlobalRankingSeason(
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingSeasonDomain>(
            Domain->GlobalRankingSeason(
                Season
            ),
            ConnectionValue
        );
    }

    FEzGlobalRankingModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzGlobalRankingModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGlobalRankingModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking2::Model::FEzGlobalRankingModelPtr> Result
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
                *Result = Gs2::UE5::Ranking2::Model::FEzGlobalRankingModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzGlobalRankingModelDomain::FModelTask>> FEzGlobalRankingModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzGlobalRankingModelDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzGlobalRankingModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking2::Model::FGlobalRankingModelPtr Item)
            {
                Callback(Gs2::UE5::Ranking2::Model::FEzGlobalRankingModel::FromModel(Item));
            }
        );
    }

    void FEzGlobalRankingModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
