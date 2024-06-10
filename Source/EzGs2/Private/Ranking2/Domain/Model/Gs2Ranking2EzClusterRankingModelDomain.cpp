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

#include "Ranking2/Domain/Model/Gs2Ranking2EzClusterRankingModelDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzClusterRankingModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzClusterRankingModelDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    FEzClusterRankingModelDomain::FEzClusterRankingModelDomain(
        Gs2::Ranking2::Domain::Model::FClusterRankingModelDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingSeasonDomainPtr FEzClusterRankingModelDomain::ClusterRankingSeason(
        const FString ClusterName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingSeasonDomain>(
            Domain->ClusterRankingSeason(
                ClusterName,
                Season
            ),
            ConnectionValue
        );
    }

    FEzClusterRankingModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzClusterRankingModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzClusterRankingModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking2::Model::FEzClusterRankingModelPtr> Result
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
                *Result = Gs2::UE5::Ranking2::Model::FEzClusterRankingModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzClusterRankingModelDomain::FModelTask>> FEzClusterRankingModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzClusterRankingModelDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzClusterRankingModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking2::Model::FClusterRankingModelPtr Item)
            {
                Callback(Gs2::UE5::Ranking2::Model::FEzClusterRankingModel::FromModel(Item));
            }
        );
    }

    void FEzClusterRankingModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
