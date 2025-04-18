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

#include "Ranking2/Domain/Model/Gs2Ranking2EzClusterRankingReceivedRewardDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzAcquireAction>>> FEzClusterRankingReceivedRewardDomain::AcquireActions() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzAcquireAction>>>();
            for (auto Value : *Domain->AcquireActions) {
                Result->Add(
                    Gs2::UE5::Ranking2::Model::FEzAcquireAction::FromModel(
                        Value
                    )
                );
            }
            return Result;
        }();
    }

    TOptional<FString> FEzClusterRankingReceivedRewardDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzClusterRankingReceivedRewardDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<FString> FEzClusterRankingReceivedRewardDomain::ClusterName() const
    {
        return Domain->ClusterName;
    }

    TOptional<int64> FEzClusterRankingReceivedRewardDomain::Season() const
    {
        return Domain->Season;
    }

    TOptional<FString> FEzClusterRankingReceivedRewardDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzClusterRankingReceivedRewardDomain::FEzClusterRankingReceivedRewardDomain(
        Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzClusterRankingReceivedRewardDomain::FModelTask::FModelTask(
        TSharedPtr<FEzClusterRankingReceivedRewardDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzClusterRankingReceivedRewardDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedRewardPtr> Result
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
                *Result = Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedReward::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzClusterRankingReceivedRewardDomain::FModelTask>> FEzClusterRankingReceivedRewardDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzClusterRankingReceivedRewardDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedRewardPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr Item)
            {
                Callback(Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedReward::FromModel(Item));
            }
        );
    }

    void FEzClusterRankingReceivedRewardDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
