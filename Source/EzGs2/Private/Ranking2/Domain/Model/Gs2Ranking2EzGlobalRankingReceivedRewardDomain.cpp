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

#include "Ranking2/Domain/Model/Gs2Ranking2EzGlobalRankingReceivedRewardDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzAcquireAction>>> FEzGlobalRankingReceivedRewardDomain::AcquireActions() const
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

    TOptional<FString> FEzGlobalRankingReceivedRewardDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzGlobalRankingReceivedRewardDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzGlobalRankingReceivedRewardDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzGlobalRankingReceivedRewardDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzGlobalRankingReceivedRewardDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<int64> FEzGlobalRankingReceivedRewardDomain::Season() const
    {
        return Domain->Season;
    }

    FEzGlobalRankingReceivedRewardDomain::FEzGlobalRankingReceivedRewardDomain(
        Gs2::Ranking2::Domain::Model::FGlobalRankingReceivedRewardDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzGlobalRankingReceivedRewardDomain::FModelTask::FModelTask(
        TSharedPtr<FEzGlobalRankingReceivedRewardDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGlobalRankingReceivedRewardDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking2::Model::FEzGlobalRankingReceivedRewardPtr> Result
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
                *Result = Gs2::UE5::Ranking2::Model::FEzGlobalRankingReceivedReward::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzGlobalRankingReceivedRewardDomain::FModelTask>> FEzGlobalRankingReceivedRewardDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzGlobalRankingReceivedRewardDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzGlobalRankingReceivedRewardPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking2::Model::FGlobalRankingReceivedRewardPtr Item)
            {
                Callback(Gs2::UE5::Ranking2::Model::FEzGlobalRankingReceivedReward::FromModel(Item));
            }
        );
    }

    void FEzGlobalRankingReceivedRewardDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
